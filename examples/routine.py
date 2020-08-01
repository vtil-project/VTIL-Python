from vtil import *


def on_block(bbl: BasicBlock) -> TaggedOrder:
    print(bbl)
    return Enumerator.obreak


def main():
    rtn = Routine.load('hello_world.vtil')
    rtn.for_each(on_block, tagged=False)
    rtn.for_each(on_block, tagged=True)


if __name__ == '__main__':
    main()
