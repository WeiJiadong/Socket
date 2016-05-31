#makefile

_BIN   = bin/
_COM   = com/
_SRC   = src/
_HEAD  = head/
_CC    = g++
_PROC  = *.cpp
_RES   = *.o
_INST  = "生成成功!"
_MV    = "安装成功!"
_UNIN  = "卸载成功!"

all : start

start :
	@g++ -c ${_SRC}${_PROC} -I ${_HEAD} \
		&& echo -e "\e[31m" ${_INST} "\e[0m"
install :
	@mv ${_RES} ${_COM} \
		&& echo -e "\e[31m" ${_MV} "\e[0m"

.PHONY : clean
clean :
	@rm ${_COM}${_RES} -f && echo -e "\e[31m" ${_UNIN} "\e[0m"
