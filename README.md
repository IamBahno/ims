# IMS

autoři: Ondřej Bahounek, Matěj Vrba

`make` přeloží program
`make run` spustí 300 kroků (100 dní) simulace šíření ropy v Mexickém zálivu
výstup se ukládá do složky `out/` v podobě fotek ve formátu .ppn
pokud chcete spustit s grafickým oknem musíte si nainstalovat knihovnu `libsfml-dev` a v souboru Makefile zakomentovat řádek `CXXFLAGS += -DREMOVE_SFML` a odkomentovat řádek `LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system`
