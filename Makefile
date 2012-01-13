CC = gcc
INPUT = udp_sender.c
OUTPUT = upd_sender
PARAMS = -01 -Wall

all:
	${CC} ${PARAMS} ${INPUT} -o ${OUTPUT} 

clean:
	rm -rf ${OUTPUT}
