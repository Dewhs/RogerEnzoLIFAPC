
# Mémo:
# $@ : nom de la cible
# $< : nom de la première dépendance
# $^ : liste des dépendances

CXX = g++
FLAGS = -Wall
SRC = src
BIN = bin
OBJ = obj

all: $(BIN)/MonProgramme

$(BIN)/MonProgramme: $(OBJ)/main.o $(OBJ)/graphe.o | $(BIN)
	$(CXX) $(FLAGS) $^ -o $@

$(OBJ)/main.o: $(SRC)/main.cpp $(SRC)/graphe.h | $(OBJ)
	$(CXX) $(FLAGS) -c $< -o $@

$(OBJ)/graphe.o: $(SRC)/graphe.cpp $(SRC)/graphe.h | $(OBJ)
	$(CXX) $(FLAGS) -c $< -o $@


# Pour créer les dossiers obj et bin si ils n'existent pas
$(OBJ) $(BIN):
	mkdir -p $@


# Pour nettoyer le projet
clean:
	rm -f $(OBJ)/*.o $(BIN)/MonProgramme

	