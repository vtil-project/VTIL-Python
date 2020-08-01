from vtil import *


def main():
    bbl = BasicBlock(0, ArchID.arm64)
    t0, zf = bbl.tmp(32, 1)
    x0, x1 = ARM64.X0, ARM64.X1
    sp = RegisterDesc.SP

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

    bbl_tracer = tracer()
    print('jz taken: {}'.format(bbl_tracer(variable(bbl.end(), zf))))


if __name__ == '__main__':
    main()
