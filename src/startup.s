.syntax unified
.cpu cortex-m4
.thumb

.global _start
.global Reset_Handler
.global _estack

.section .isr_vector, "a", %progbits
.type _vector_table, %object
_vector_table:
    .word _estack            // Initial stack pointer
    .word Reset_Handler      // Reset handler
    .word NMI_Handler        // NMI
    .word HardFault_Handler  // Hard fault
    .word Default_Handler    // MemManage
    .word Default_Handler    // BusFault
    .word Default_Handler    // UsageFault
    .word 0                  // Reserved
    .word 0
    .word 0
    .word 0
    .word Default_Handler    // SVC
    .word Default_Handler    // DebugMon
    .word 0                  // Reserved
    .word Default_Handler    // PendSV
    .word Default_Handler    // SysTick

    // IRQs (up to 91 IRQs for STM32F429)
    .rept 91
    .word Default_Handler
    .endr

.size _vector_table, . - _vector_table

.section .text.Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    // Copy .data section from flash to RAM
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
1:
    cmp r0, r1
    ittt lt
    ldrlt r3, [r2], #4
    strlt r3, [r0], #4
    blt 1b

    // Zero initialize the .bss section
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
2:
    cmp r0, r1
    itt lt
    strlt r2, [r0], #4
    blt 2b

    // Call main()
    bl main

    // If main returns, loop forever
1:  b 1b

.size Reset_Handler, . - Reset_Handler

// Default interrupt handlers
.type Default_Handler, %function
Default_Handler:
    b .

.size Default_Handler, . - Default_Handler

.weak NMI_Handler
.thumb_set NMI_Handler, Default_Handler

.weak HardFault_Handler
.thumb_set HardFault_Handler, Default_Handler

.weak MemManage_Handler
.thumb_set MemManage_Handler, Default_Handler

.weak BusFault_Handler
.thumb_set BusFault_Handler, Default_Handler

.weak UsageFault_Handler
.thumb_set UsageFault_Handler, Default_Handler

.weak SVC_Handler
.thumb_set SVC_Handler, Default_Handler

.weak DebugMon_Handler
.thumb_set DebugMon_Handler, Default_Handler

.weak PendSV_Handler
.thumb_set PendSV_Handler, Default_Handler

.weak SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler

/* IRQs (optional up to 91 IRQs on STM32F429) */
//.rept 91
//    .weak IRQ_Handler_\@
//    .thumb_set IRQ_Handler_\@, Default_Handler
//.endr

