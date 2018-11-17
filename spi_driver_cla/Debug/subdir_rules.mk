################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Cla.obj: ../Cla.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Cla.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ClaTasks_C.obj: ../ClaTasks_C.cla $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="ClaTasks_C.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CodeStartBranch.obj: ../CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="CodeStartBranch.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DefaultIsr_9_10.obj: ../DefaultIsr_9_10.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="DefaultIsr_9_10.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DelayUs.obj: ../DelayUs.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="DelayUs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

EPwm.obj: ../EPwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="EPwm.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_Gpio.obj: ../F2837xD_Gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_Gpio.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2837xD_Spi.obj: ../F2837xD_Spi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_Spi.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Main.obj: ../Main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PieCtrl.obj: ../PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="PieCtrl.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PieVect.obj: ../PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="PieVect.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SysCtrl.obj: ../SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="SysCtrl.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Watchdog.obj: ../Watchdog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla/Lab_common/include" --include_path="C:/Users/Troy/Desktop/Senior Software/Senior_Design/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Watchdog.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


