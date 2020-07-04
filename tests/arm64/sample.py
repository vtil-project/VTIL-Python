from vtil import *


def main():
    bbl = basic_block.begin(0, architecture_identifier.arm64)
    t0, zf = bbl.tmp(32, 1)
    x0, x1 = arm64_reg.X0, arm64_reg.X1
    sp = register_desc.SP
    
    bbl.mov(x0, 100)    \
       .push(x0)        \
       .mov(x1, x0)     \
       .push(x1)        \
       .ldd(t0, sp, 4)  \
       .add(t0, 100)    \
       .store(sp, 4, t0)\
       .pop(x1)         \
       .pop(x0)         \
       .mov(x0, x1)     \
       .mov(t0, x0)     \
       .sub(t0, 100)    \
       .te(zf, t0, 0)
    
    print('jz taken: {}'.format(tracer()(variable(bbl.end(), zf))))


if __name__ == '__main__':
    main()
