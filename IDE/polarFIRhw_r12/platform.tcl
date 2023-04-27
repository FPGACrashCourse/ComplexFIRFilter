# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\ComplexFIRFilter\polarFIRhw_r12\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\ComplexFIRFilter\polarFIRhw_r12\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {polarFIRhw_r12}\
-hw {D:\ComplexFIRFilter\hw\polarFIRhw_r12.xsa}\
-out {D:/ComplexFIRFilter}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {polarFIRhw_r12}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform generate
platform generate
platform clean
platform generate
platform clean
platform generate
platform generate -domains standalone_ps7_cortexa9_0,zynq_fsbl 
