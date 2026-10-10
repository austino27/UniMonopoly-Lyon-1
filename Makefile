# Compilateur
CXX = g++
CXXFLAGS = -Wall -g -Iinclude

# SDL
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LIBS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DOC_DIR = doc

# Executables
TARGET_TXT = $(BIN_DIR)/JeuTXT
TARGET_SDL = $(BIN_DIR)/JeuSDL

# Sources communes
SRC_COMMON = \
$(SRC_DIR)/Joueur.cpp \
$(SRC_DIR)/Case.cpp \
$(SRC_DIR)/Plateau.cpp \
$(SRC_DIR)/De.cpp \
$(SRC_DIR)/Propriete.cpp \
$(SRC_DIR)/Banque.cpp \
$(SRC_DIR)/Carte.cpp \
$(SRC_DIR)/Jeu.cpp

# Sources TXT
SRC_TXT = $(SRC_COMMON) \
$(SRC_DIR)/mainTXT.cpp \
$(SRC_DIR)/JeuTXT.cpp

# Sources SDL
SRC_SDL = $(SRC_COMMON) \
$(SRC_DIR)/mainSDL.cpp \
$(SRC_DIR)/JeuSDL.cpp \
$(SRC_DIR)/Menu.cpp \
$(SRC_DIR)/GestionnairePartiesSDL.cpp \
$(SRC_DIR)/Bouton.cpp

# Objets
OBJ_TXT = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_TXT))
OBJ_SDL = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_SDL))

# Règle principale
all: $(TARGET_TXT) $(TARGET_SDL)

# Jeu texte
$(TARGET_TXT): $(OBJ_TXT) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_TXT) -o $@

# Jeu SDL
$(TARGET_SDL): $(OBJ_SDL) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) $(OBJ_SDL) -o $@ $(SDL_LIBS)

# Compilation objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -c $< -o $@

# Création dossiers
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Documentation Doxygen
docu:
	doxygen doc/Doxyfile

# Nettoyage objets + documentation
clean:
	rm -f $(OBJ_DIR)/*.o
	rm -rf $(DOC_DIR)/html
	rm -rf $(DOC_DIR)/latex

# Nettoyage total
veryclean: clean
	rm -f $(TARGET_TXT)
	rm -f $(TARGET_SDL)
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)