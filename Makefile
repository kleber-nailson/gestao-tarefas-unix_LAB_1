# Nome do compilador
CC=gcc

# Opções de compilação
CFLAGS=-Wall -g

# Nome do arquivo executável
EXEC=gestor_tarefas

# Arquivos fonte
SRC=gestor_tarefas.c

# Arquivos objeto
OBJ=$(SRC:.c=.o)

# Regra padrão
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

# Regra para executar
run: $(EXEC)
	./$(EXEC)
