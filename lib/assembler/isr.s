.global isr_stub_table
.extern exception_handler

# Macro for ISR stubs with error codes
.macro isr_err_stub num
isr_stub_\num:
    call exception_handler
    iret
.endm

# Macro for ISR stubs without error codes
.macro isr_no_err_stub num
isr_stub_\num:
    call exception_handler
    iret
.endm

# Generate all ISR stubs
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

# ISR stub table
.section .data
isr_stub_table:
    .int isr_stub_0
    .int isr_stub_1
    .int isr_stub_2
    .int isr_stub_3
    .int isr_stub_4
    .int isr_stub_5
    .int isr_stub_6
    .int isr_stub_7
    .int isr_stub_8
    .int isr_stub_9
    .int isr_stub_10
    .int isr_stub_11
    .int isr_stub_12
    .int isr_stub_13
    .int isr_stub_14
    .int isr_stub_15
    .int isr_stub_16
    .int isr_stub_17
    .int isr_stub_18
    .int isr_stub_19
    .int isr_stub_20
    .int isr_stub_21
    .int isr_stub_22
    .int isr_stub_23
    .int isr_stub_24
    .int isr_stub_25
    .int isr_stub_26
    .int isr_stub_27
    .int isr_stub_28
    .int isr_stub_29
    .int isr_stub_30
    .int isr_stub_31
