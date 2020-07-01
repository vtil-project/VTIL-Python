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
       .add(t0, 100)    \
       .pop(x1)         \
       .pop(x0)         \
       .mov(x0, x1)     \
       .mov(t0, x0)     \
       .sub(t0, 100)    \
       .te(zf, t0, 0)
    
    print(f'jz taken: {tracer()(variable(bbl.end(), zf))}')


if __name__ == '__main__':
    main()
