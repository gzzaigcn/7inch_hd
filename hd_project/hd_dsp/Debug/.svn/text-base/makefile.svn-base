################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/Program Files/CCS5.4/ccsv5/tools/compiler/c6000_7.4.2

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./src/alg/img_alg.obj" \
"./src/alg/ImageSetNA_sa.obj" \
"./src/alg/ImageCopy_sa.obj" \
"./src/alg/ImageCopyNA_sa.obj" \
"./src/alg/GrayTransTable_sa.obj" \
"./src/alg/GrayTransStatTable_sa.obj" \
"./src/alg/ContrastBrightSaturationTable_sa.obj" \
"./src/alg/ContrastBrightSaturationStatTable_sa.obj" \
"./src/alg/ColorTransTable_sa.obj" \
"./src/alg/ColorTransStatTable_sa.obj" \
"./src/alg/CalBlockGray_sa.obj" \
"./src/app/realplay.obj" \
"./src/app/norflash_fs.obj" \
"./src/app/main.obj" \
"./src/app/camera.obj" \
"./src/drivers/wv511.obj" \
"./src/drivers/vector.obj" \
"./src/drivers/tmd2771.obj" \
"./src/drivers/ov5640.obj" \
"./src/drivers/ov2710.obj" \
"./src/drivers/norflash.obj" \
"./src/drivers/lcd.obj" \
"./src/drivers/key.obj" \
"./src/drivers/isr.obj" \
"./src/drivers/hdmi.obj" \
"./src/drivers/dm6437_vpfe.obj" \
"./src/drivers/dm6437_vpbe.obj" \
"./src/drivers/dm6437_uart.obj" \
"./src/drivers/dm6437_psc.obj" \
"./src/drivers/dm6437_pll.obj" \
"./src/drivers/dm6437_mcbsp.obj" \
"./src/drivers/dm6437_init.obj" \
"./src/drivers/dm6437_i2c.obj" \
"./src/drivers/dm6437_gpio.obj" \
"./src/drivers/dm6437_edma3.obj" \
"./src/drivers/dm6437_ddr2.obj" \
"./src/drivers/dm6437_cache.obj" \
"./src/drivers/buzzer.obj" \
-l"libc.a" \
-l"E:\CCS5.4.0\7inch_Aid\lib\jpegdec_ti.l64P" \
"E:/CCS5.4.0/7inch_Aid/source/app/linker.cmd" \
"E:/CCS5.4.0/7inch_Aid/lib/IQmath_ROM_c643x.lib" \
"E:/CCS5.4.0/7inch_Aid/lib/IQmath_c64x+.lib" \
"E:/CCS5.4.0/7inch_Aid/lib/SEED_DEC6437Bsl.lib" \
"E:/CCS5.4.0/7inch_Aid/lib/TOPV_scaler.lib" \
"E:/CCS5.4.0/7inch_Aid/lib/csl_davinciC64plus.lib" \
"E:/CCS5.4.0/7inch_Aid/lib/csl_sysservicesdavinci.lib" \
"E:/CCS5.4.0/7inch_Aid/lib/dspcsl_davinci.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include targetConfigs/subdir_vars.mk
-include src/drivers/subdir_vars.mk
-include src/app/subdir_vars.mk
-include src/alg/subdir_vars.mk
-include lib/subdir_vars.mk
-include targetConfigs/subdir_rules.mk
-include src/drivers/subdir_rules.mk
-include src/app/subdir_rules.mk
-include src/alg/subdir_rules.mk
-include lib/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: hd_dsp.out

# Tool invocations
hd_dsp.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"D:/Program Files/CCS5.4/ccsv5/tools/compiler/c6000_7.4.2/bin/cl6x" -mv64+ --abi=coffabi -g --relaxed_ansi --define=dm6437 --display_error_number --diag_warning=225 --diag_wrap=off -z --stack_size=0x800 -m"hd_dsp.map" --heap_size=0x800 -i"D:/Program Files/CCS5.4/ccsv5/tools/compiler/c6000_7.4.2/lib" -i"E:/CCS5.4.0/7inch_Aid/lib" -i"D:/Program Files/CCS5.4/ccsv5/tools/compiler/c6000_7.4.2/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="hd_dsp_linkInfo.xml" --rom_model -o "hd_dsp.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_EXECUTABLE_OUTPUTS__QUOTED) "hd_dsp.out"
	-$(RM) "src\drivers\buzzer.pp" "src\drivers\dm6437_cache.pp" "src\drivers\dm6437_ddr2.pp" "src\drivers\dm6437_edma3.pp" "src\drivers\dm6437_gpio.pp" "src\drivers\dm6437_i2c.pp" "src\drivers\dm6437_init.pp" "src\drivers\dm6437_mcbsp.pp" "src\drivers\dm6437_pll.pp" "src\drivers\dm6437_psc.pp" "src\drivers\dm6437_uart.pp" "src\drivers\dm6437_vpbe.pp" "src\drivers\dm6437_vpfe.pp" "src\drivers\hdmi.pp" "src\drivers\isr.pp" "src\drivers\key.pp" "src\drivers\lcd.pp" "src\drivers\norflash.pp" "src\drivers\ov2710.pp" "src\drivers\ov5640.pp" "src\drivers\tmd2771.pp" "src\drivers\wv511.pp" "src\app\camera.pp" "src\app\main.pp" "src\app\norflash_fs.pp" "src\app\realplay.pp" "src\alg\img_alg.pp" 
	-$(RM) "src\drivers\buzzer.obj" "src\drivers\dm6437_cache.obj" "src\drivers\dm6437_ddr2.obj" "src\drivers\dm6437_edma3.obj" "src\drivers\dm6437_gpio.obj" "src\drivers\dm6437_i2c.obj" "src\drivers\dm6437_init.obj" "src\drivers\dm6437_mcbsp.obj" "src\drivers\dm6437_pll.obj" "src\drivers\dm6437_psc.obj" "src\drivers\dm6437_uart.obj" "src\drivers\dm6437_vpbe.obj" "src\drivers\dm6437_vpfe.obj" "src\drivers\hdmi.obj" "src\drivers\isr.obj" "src\drivers\key.obj" "src\drivers\lcd.obj" "src\drivers\norflash.obj" "src\drivers\ov2710.obj" "src\drivers\ov5640.obj" "src\drivers\tmd2771.obj" "src\drivers\vector.obj" "src\drivers\wv511.obj" "src\app\camera.obj" "src\app\main.obj" "src\app\norflash_fs.obj" "src\app\realplay.obj" "src\alg\CalBlockGray_sa.obj" "src\alg\ColorTransStatTable_sa.obj" "src\alg\ColorTransTable_sa.obj" "src\alg\ContrastBrightSaturationStatTable_sa.obj" "src\alg\ContrastBrightSaturationTable_sa.obj" "src\alg\GrayTransStatTable_sa.obj" "src\alg\GrayTransTable_sa.obj" "src\alg\ImageCopyNA_sa.obj" 
	-$(RM) "src\alg\ImageCopy_sa.obj" "src\alg\ImageSetNA_sa.obj" "src\alg\img_alg.obj" 
	-$(RM) "src\alg\CalBlockGray_sa.pp" "src\alg\ColorTransStatTable_sa.pp" "src\alg\ColorTransTable_sa.pp" "src\alg\ContrastBrightSaturationStatTable_sa.pp" "src\alg\ContrastBrightSaturationTable_sa.pp" "src\alg\GrayTransStatTable_sa.pp" "src\alg\GrayTransTable_sa.pp" "src\alg\ImageCopyNA_sa.pp" "src\alg\ImageCopy_sa.pp" "src\alg\ImageSetNA_sa.pp" 
	-$(RM) "src\drivers\vector.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
