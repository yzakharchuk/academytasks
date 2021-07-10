## Try to reach the CPU cache limitations

Compare times in the next two situations:
Try to write something 1’049’600 times in 2*32 bytes (<L1 cache)
Try to write something  64 times in 4*256 Kbytes (>L2 cache)
And think about trying to write 1’000’00 times in 4*32 + 1 Kbytes (between L1& L2).