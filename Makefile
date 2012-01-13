CC = gcc
INPUT = udp_sender.c
OUTPUT = upd_sender
PARAMS = -01 -Wall
INCLUDE_DIR = ./include/

all:
	${CC} ${PARAMS} -I${INCLUDE_DIR} ${INPUT} -o ${OUTPUT} 

clean:
	rm -rf ${OUTPUT}
