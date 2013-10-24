# mention dynamic linking!
import struct

charp = gdb.lookup_type('char').pointer()
intp = gdb.lookup_type('int').pointer()
intpp = intp.pointer()

def cell(bytes):
  return struct.unpack('i',bytes)[0]

def to_float(floatbits):
  return struct.unpack('f',struct.pack('I',floatbits))[0]

def read_string(ptrbits):
  return gdb.Value(ptrbits).cast(charp).string()

def convert_args(fmt, args):
  types = [s[0] for s in fmt.split('%')[1:]]
  unpack = {'s':read_string, 'd':int, 'x':int, 'f':to_float}
  return tuple([unpack[t](a) for t,a in zip(types,args)])

def print_messages(words):
  i = 0
  while i<len(words):
    fmt = read_string(words[i])
    n = words[i+1]
    args = [int(words[j]) for j in xrange(i+2,i+2+n)]
    print fmt % convert_args(fmt, args), 
    i += n+2

class dprintf(gdb.Command):
  '''
  dprintf <filename>: convert the messages in filename to text
  dprintf with no arguments: convert g_dbuf to text - useful with core dumps
  '''
  def __init__(self):
    gdb.Command.__init__(self, 'dprintf', gdb.COMMAND_DATA)

  def invoke(self, arg, from_tty):
    if arg:
      bytes = open(arg,'rb').read()
      words = [cell(bytes[i:i+4]) for i in xrange(0, len(bytes), 4)]
    else:
      # note how we avoid counting on DWARF debug info
      data = gdb.parse_and_eval('&g_data').cast(intp)
      buf = gdb.parse_and_eval('&g_dbuf').cast(intpp)
      words = [int(data[i]) for i in xrange(buf.dereference() - data)]
    print_messages(words)

dprintf()
