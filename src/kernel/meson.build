cxx_compiler = find_program('i686-elf-g++')
c_compiler = find_program('i686-elf-gcc')
objcopy = find_program('i686-elf-objcopy')

kernel_binary_name = 'kernel.bin'

gcc_args = '-c -fpic -ffreestanding'
#add_global_arguments(gcc_args, language : 'c')
#add_global_arguments(gcc_args, language : 'c++')

kernel_sources = []
kernel_includes = []

subdir('kernel')

include_directories(kernel_includes)

#executable(kernel_binary_name, kernel_sources)
result = run_command('i686-elf-g++', gcc_args, '-o ' + '../build' + '/' + kernel_binary_name, 'kernel/kernel.cpp')

if result.returncode() == 0
	message('Compiled kernel')
else
	error('Failed to compile kernel')
endif
