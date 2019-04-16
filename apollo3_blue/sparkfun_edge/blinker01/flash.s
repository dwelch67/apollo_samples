
.cpu cortex-m0
.thumb

.thumb_func
.global _start
_start:
stacktop: .word 0x10011000
.word reset
.word done
.word done

.word done
.word done
.word done
.word done

.word done
.word done
.word done
.word done

.word done
.word done
.word done
.word done

.thumb_func
reset:
    bl notmain
    b done

.thumb_func
done:
    b .

.thumb_func
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.thumb_func
.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.thumb_func
.globl dummy
dummy:
    bx lr


