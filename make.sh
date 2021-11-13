#!/bin/sh -ex

mkdir -p build

FILES="
program.h
program_rain.h
program_rain.c
all.c
format.c
format.h
i2c.h
i2c_init.c
i2c_reset.c
i2c_start.c
i2c_stop.c
i2c_write.c
main.c
main2.c
rom.h
rom.c
framebuffer.h
framebuffer_init.c
framebuffer_blit.c
framebuffer_send.c
framebuffer_text.c
framebuffer_set.c
framebuffer_vline.c
transitions.h
transition_vbar.c
ssd1306.h
ssd1306_clear.c
ssd1306_display_all_on.c
ssd1306_display_all_on_resume.c
ssd1306_display_off.c
ssd1306_display_on.c
ssd1306_init.c
ssd1306_data.c
ssd1306_send_command.c
ssd1306_set_charge_pump.c
ssd1306_set_clock_divider.c
ssd1306_set_column_address.c
ssd1306_set_com_output_scan.c
ssd1306_horizontal_scroll.c
ssd1306_set_com_pins_configuration.c
ssd1306_set_contrast.c
ssd1306_set_display_offset.c
ssd1306_set_display_start_line.c
ssd1306_set_invert.c
ssd1306_set_memory_addressing_mode.c
ssd1306_set_multiplex_ratio.c
ssd1306_set_page_address.c
ssd1306_set_page_column_address.c
ssd1306_set_page_start_address.c
ssd1306_set_precharge_period.c
ssd1306_set_segment_remap.c
ssd1306_set_vcom_deselect.c
uart.h
uart_getchar.c
uart_init.c
uart_putchar.c
uart_puts.c
uart_puts_p.c
"

for f in ${FILES}
do
  clang-format -i "$f"
done

./c-compile build/program_rain.o program_rain.c
./c-compile build/all.o all.c
./c-compile build/format.o format.c
./c-compile build/i2c_init.o i2c_init.c
./c-compile build/i2c_reset.o i2c_reset.c
./c-compile build/i2c_start.o i2c_start.c
./c-compile build/i2c_stop.o i2c_stop.c
./c-compile build/i2c_write.o i2c_write.c
./c-compile build/rom.o rom.c
./c-compile build/framebuffer_init.o framebuffer_init.c
./c-compile build/framebuffer_blit.o framebuffer_blit.c
./c-compile build/framebuffer_send.o framebuffer_send.c
./c-compile build/framebuffer_text.o framebuffer_text.c
./c-compile build/framebuffer_set.o framebuffer_set.c
./c-compile build/framebuffer_vline.o framebuffer_vline.c
./c-compile build/main.o main.c
./c-compile build/main2.o main2.c
./c-compile build/transition_vbar.o transition_vbar.c
./c-compile build/ssd1306_clear.o ssd1306_clear.c
./c-compile build/ssd1306_display_all_on.o ssd1306_display_all_on.c
./c-compile build/ssd1306_display_all_on_resume.o ssd1306_display_all_on_resume.c
./c-compile build/ssd1306_display_off.o ssd1306_display_off.c
./c-compile build/ssd1306_display_on.o ssd1306_display_on.c
./c-compile build/ssd1306_init.o ssd1306_init.c
./c-compile build/ssd1306_data.o ssd1306_data.c
./c-compile build/ssd1306_send_command.o ssd1306_send_command.c
./c-compile build/ssd1306_set_charge_pump.o ssd1306_set_charge_pump.c
./c-compile build/ssd1306_horizontal_scroll.o ssd1306_horizontal_scroll.c
./c-compile build/ssd1306_set_clock_divider.o ssd1306_set_clock_divider.c
./c-compile build/ssd1306_set_column_address.o ssd1306_set_column_address.c
./c-compile build/ssd1306_set_com_output_scan.o ssd1306_set_com_output_scan.c
./c-compile build/ssd1306_set_com_pins_configuration.o ssd1306_set_com_pins_configuration.c
./c-compile build/ssd1306_set_contrast.o ssd1306_set_contrast.c
./c-compile build/ssd1306_set_display_offset.o ssd1306_set_display_offset.c
./c-compile build/ssd1306_set_display_start_line.o ssd1306_set_display_start_line.c
./c-compile build/ssd1306_set_invert.o ssd1306_set_invert.c
./c-compile build/ssd1306_set_memory_addressing_mode.o ssd1306_set_memory_addressing_mode.c
./c-compile build/ssd1306_set_multiplex_ratio.o ssd1306_set_multiplex_ratio.c
./c-compile build/ssd1306_set_page_address.o ssd1306_set_page_address.c
./c-compile build/ssd1306_set_page_column_address.o ssd1306_set_page_column_address.c
./c-compile build/ssd1306_set_page_start_address.o ssd1306_set_page_start_address.c
./c-compile build/ssd1306_set_precharge_period.o ssd1306_set_precharge_period.c
./c-compile build/ssd1306_set_segment_remap.o ssd1306_set_segment_remap.c
./c-compile build/ssd1306_set_vcom_deselect.o ssd1306_set_vcom_deselect.c
./c-compile build/uart_getchar.o uart_getchar.c
./c-compile build/uart_init.o uart_init.c
./c-compile build/uart_putchar.o uart_putchar.c
./c-compile build/uart_puts.o uart_puts.c
./c-compile build/uart_puts_p.o uart_puts_p.c

ar rc build/framebuffer.a \
build/framebuffer_init.o \
build/framebuffer_blit.o \
build/framebuffer_send.o \
build/framebuffer_text.o \
build/framebuffer_vline.o \
build/framebuffer_set.o
ranlib build/framebuffer.a

ar rc build/uart.a \
build/uart_getchar.o \
build/uart_init.o \
build/uart_putchar.o \
build/uart_puts.o \
build/uart_puts_p.o
ranlib build/uart.a

ar rc build/i2c.a \
build/i2c_init.o \
build/i2c_reset.o \
build/i2c_start.o \
build/i2c_stop.o \
build/i2c_write.o
ranlib build/i2c.a

ar rc build/transitions.a \
build/transition_vbar.o
ranlib build/transitions.a

ar rc build/program.a \
build/program_rain.o
ranlib build/program.a

ar rc build/ssd1306.a \
build/ssd1306_display_off.o \
build/ssd1306_display_on.o \
build/ssd1306_display_all_on.o \
build/ssd1306_display_all_on_resume.o \
build/ssd1306_horizontal_scroll.o \
build/ssd1306_init.o \
build/ssd1306_clear.o \
build/ssd1306_data.o \
build/ssd1306_send_command.o \
build/ssd1306_set_charge_pump.o \
build/ssd1306_set_clock_divider.o \
build/ssd1306_set_com_output_scan.o \
build/ssd1306_set_com_pins_configuration.o \
build/ssd1306_set_contrast.o \
build/ssd1306_set_column_address.o \
build/ssd1306_set_page_column_address.o \
build/ssd1306_set_page_start_address.o \
build/ssd1306_set_page_address.o \
build/ssd1306_set_display_offset.o \
build/ssd1306_set_display_start_line.o \
build/ssd1306_set_invert.o \
build/ssd1306_set_memory_addressing_mode.o \
build/ssd1306_set_multiplex_ratio.o \
build/ssd1306_set_precharge_period.o \
build/ssd1306_set_segment_remap.o \
build/ssd1306_set_vcom_deselect.o
ranlib build/ssd1306.a

./c-link build/all build/all.o
./c-link build/main build/main.o build/format.o build/ssd1306.a build/i2c.a build/uart.a
./c-link build/main2 build/main2.o build/format.o build/program.a build/transitions.a build/framebuffer.a build/ssd1306.a build/i2c.a build/uart.a build/rom.o

./hex build/main.hex build/main
./hex build/main2.hex build/main2
./hex build/all.hex build/all
