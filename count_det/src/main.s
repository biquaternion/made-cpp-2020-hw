.text
.global count_det

count_det:
    ldr r1, [r0]      // 1
    ldr r4, [r0, #16] // 5
    ldr r5, [r0, #32] // 9
    ldr r6, [r0, #20] // 6
    ldr r7, [r0, #28] // 8
    mul r4, r5, r4
    mul r5, r6, r7
    sub r5, r4, r5
    mul r1, r5, r1

    ldr r2, [r0, #4] // 2
    ldr r4, [r0, #20] // 6
    ldr r5, [r0, #24] // 7
    ldr r6, [r0, #12] // 4
    ldr r7, [r0, #32] // 9
    mul r4, r5, r4
    mul r5, r6, r7
    sub r5, r4, r5
    mul r2, r5, r2

    ldr r3, [r0, #8] // 3
    ldr r4, [r0, #12] // 4
    ldr r5, [r0, #28] // 8
    ldr r6, [r0, #16] // 5
    ldr r7, [r0, #24] // 7
    mul r4, r5, r4
    mul r5, r6, r7
    sub r5, r4, r5
    mul r3, r5, r3

    add r1, r2, r1
    add r1, r3, r1
    mov r0, r1
    bx lr
