################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F2837xD_headers/source/F2837xD_GlobalVariableDefs.obj: ../F2837xD_headers/source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/spi_driver_cla/F2837xD_headers/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_1_00_05_00/device_support/f2837xd/headers/include" --include_path="C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/spi_driver_cla/Lab_common/include" --include_path="C:/Users/meserwinowski/OneDrive - University of Florida/UF/Senior Design EEL4924C/spi_driver_cla" --include_path="C:/ti/F2837xD/Device_support/F2837xD_common/include" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="F2837xD_headers/source/F2837xD_GlobalVariableDefs.d_raw" --obj_directory="F2837xD_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


