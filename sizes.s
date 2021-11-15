.text

.global size_bss
.global size_text
.global size_data
.global size_stack

size_bss:
  ldi r24,lo8(__bss_end)
  ldi r25,hi8(__bss_end)
  ldi r18,lo8(__bss_start)
  ldi r19,hi8(__bss_start)
  sub r24,r18
  sbc r25,r19
  ret

size_text:
  ldi r24,lo8(_etext)
  ldi r25,hi8(_etext)
  ret

size_data:
  ldi r24,lo8(__data_end)
  ldi r25,hi8(__data_end)
  ldi r18,lo8(__data_start)
  ldi r19,hi8(__data_start)
  sub r24,r18
  sbc r25,r19
  ret

size_stack:
  ldi r24,lo8(__stack)
  ldi r25,hi8(__stack)
  in r18,0x3D
  in r19,0x3E
  sub r24,r18
  sbc r25,r19
  ret

