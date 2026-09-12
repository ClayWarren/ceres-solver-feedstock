import pathlib, struct, sys
b = pathlib.Path(sys.argv[1]).read_bytes()
assert b[:2] == b'MZ'
o = struct.unpack_from('<I', b, 0x3c)[0]
assert b[o:o+4] == b'PE\0\0'
assert struct.unpack_from('<H', b, o+4)[0] == 0xaa64
print('Native ARM64 consumer verified')
