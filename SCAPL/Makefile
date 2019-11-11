Test: main.o Program.o Identifier.o Label.o Variable.o Operand.o ReadStmt.o PrintStmt.o JumpStmt.o JMoreStmt.o EndStmt.o DeclIntStmt.o CompStmt.o
	g++ -o Test main.o Program.o Identifier.o Label.o Variable.o Operand.o ReadStmt.o PrintStmt.o JumpStmt.o JMoreStmt.o EndStmt.o DeclIntStmt.o CompStmt.o
	
main.o: main.cc Program.h
	g++ -c main.cc

Program.o: Program.cc Program.h Statement.h Identifier.h ./STMTs/CompStmt.h ./STMTs/DeclIntStmt.h ./STMTs/EndStmt.h ./STMTs/JMoreStmt.h ./STMTs/JumpStmt.h ./STMTs/PrintStmt.h ./STMTs/ReadStmt.h 
	g++ -c Program.cc

Identifier.o: Identifier.cc Identifier.h
	g++ -c Identifier.cc

Label.o: Label.cc Label.h Identifier.h
	g++ -c Label.cc

Variable.o: Variable.cc Variable.h Identifier.h
	g++ -c Variable.cc

Operand.o: Operand.cc Operand.h Identifier.h
	g++ -c Operand.cc

./STMTs/ReadStmt.o: ./STMTs/ReadStmt.cc ./STMTs/ReadStmt.h Statement.h Program.h
	g++ -c ./STMTs/ReadStmt.cc

./STMTs/PrintStmt.o: ./STMTs/PrintStmt.cc ./STMTs/PrintStmt.h Statement.h Program.h
	g++ -c ./STMTs/PrintStmt.cc

./STMTs/JumpStmt.o: ./STMTs/JumpStmt.cc ./STMTs/JumpStmt.h Statement.h Program.h
	g++ -c ./STMTs/JumpStmt.cc

./STMTs/JMoreStmt.o: ./STMTs/JMoreStmt.cc ./STMTs/JMoreStmt.h Statement.h Program.h
	g++ -c ./STMTs/JMoreStmt.cc

./STMTs/EndStmt.o: ./STMTs/EndStmt.cc ./STMTs/EndStmt.h Statement.h Program.h
	g++ -c ./STMTs/EndStmt.cc

./STMTs/DeclIntStmt.o: ./STMTs/DeclIntStmt.cc ./STMTs/DeclIntStmt.h Statement.h Program.h
	g++ -c ./STMTs/DeclIntStmt.cc

./STMTs/CompStmt.o: ./STMTs/CompStmt.cc ./STMTs/CompStmt.h Statement.h Program.h
	g++ -c ./STMTs/CompStmt.cc