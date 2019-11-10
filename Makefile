CC=g++
CFLAGS= -c -o3
SCAPLDIR=./SCAPL/
STMTDIR=./SCAPL/STMTs/
UIDIR=./ui/

# Master Compile
SCAPES: $(SCAPLDIR)Program.o $(SCAPLDIR)Identifier.o $(SCAPLDIR)Label $(SCAPLDIR)Variable $(SCAPLDIR)Operand $(SCAPLDIR)Statement.o $(STMTDIR)AddStmt.o $(STMTDIR)CompStmt.o $(STMTDIR)DeclArrStmt.o $(STMTDIR)DeclIntStmt.o $(STMTDIR)EndStmt.o $(STMTDIR)JEqStmt.o $(STMTDIR)JLessStmt.o $(STMTDIR)JMoreStmt.o $(STMTDIR)JumpStmt.o $(STMTDIR)MovStmt.o $(STMTDIR)PrintStmt.o $(STMTDIR)ReadStmt.o
	$(CC) -o SCAPES

# SCAPL Compile

Program.o: $(SCAPLDIR)Program.cc $(SCAPLDIR)Program.h $(SCAPLDIR)Identifier.h $(SCAPLDIR)Statement.h $(STMTDIR)AddStmt.h $(STMTDIR)CompStmt.h $(STMTDIR)DeclArrStmt.h $(STMTDIR)DeclIntStmt.h $(STMTDIR)EndStmt.h $(STMTDIR)JEqStmt.h $(STMTDIR)JLessStmt.h $(STMTDIR)JMoreStmt.h $(STMTDIR)JumpStmt.h $(STMTDIR)MovStmt.h $(STMTDIR)PrintStmt.h $(STMTDIR)ReadStmt.h
	$(CC) $(CFLAGS) $(SCAPLDIR)Program.cc

$(STMTDIR)AddStmt.o: $(STMTDIR)AddStmt.cc $(STMTDIR)AddStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)AddStmt.cc

$(STMTDIR)CompStmt.o: $(STMTDIR)CompStmt.cc $(STMTDIR)CompStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)CompStmt.cc

$(STMTDIR)DeclArrStmt.o: $(STMTDIR)DeclArrStmt.cc $(STMTDIR)DeclArrStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)DeclArrStmt.cc

$(STMTDIR)DeclIntStmt.o: $(STMTDIR)DeclIntStmt.cc $(STMTDIR)DeclIntStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)DeclIntStmt.cc

$(STMTDIR)EndStmt.o: $(STMTDIR)EndStmt.cc $(STMTDIR)EndStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)EndStmt.cc

$(STMTDIR)JEqStmt.o: $(STMTDIR)JEqStmt.cc $(STMTDIR)JEqStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)JEqStmt.cc

$(STMTDIR)JLessStmt.o: $(STMTDIR)JLessStmt.cc $(STMTDIR)JLessStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)JLessStmt.cc

$(STMTDIR)JMoreStmt.o: $(STMTDIR)JMoreStmt.cc $(STMTDIR)JMoreStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)JMoreStmt.cc

$(STMTDIR)JumpStmt.o: $(STMTDIR)JumpStmt.cc $(STMTDIR)JumpStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)JumpStmt.cc

$(STMTDIR)MovStmt.o: $(STMTDIR)MovStmt.cc $(STMTDIR)MovStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)MovStmt.cc

$(STMTDIR)PrintStmt.o: $(STMTDIR)PrintStmt.cc $(STMTDIR)PrintStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)PrintStmt.cc

$(STMTDIR)ReadStmt.o: $(STMTDIR)ReadStmt.cc $(STMTDIR)ReadStmt.h $(SCAPLDIR)Statement.h
	$(CC) $(CFLAGS) $(STMTDIR)ReadStmt.cc

Operand.o: $(SCAPLDIR)Operand.cc $(SCAPLDIR)Operand.h $(SCAPLDIR)Identifier.h
	$(CC) $(CFLAGS) $(SCAPLDIR)Operand.cc

Variable.o: $(SCAPLDIR)Variable.cc $(SCAPLDIR)Variable.h $(SCAPLDIR)Identifier.h
	$(CC) $(CFLAGS) $(SCAPLDIR)Variable.cc

Label.o: $(SCAPLDIR)Label.cc $(SCAPLDIR)Label.h $(SCAPLDIR)Identifier.h
	$(CC) $(CFLAGS) $(SCAPLDIR)Label.cc

Identifier.o: $(SCAPLDIR)Identifier.cc $(SCAPLDIR)Identifier.h
	$(CC) $(CFLAGS) $(SCAPLDIR)Identifier.cc

# UI Compile

# FS Compile
