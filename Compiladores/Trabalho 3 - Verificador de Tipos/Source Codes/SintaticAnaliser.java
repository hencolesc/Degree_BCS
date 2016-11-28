/*
 * Créditos a destacar:
 * http://www.regexplanet.com/advanced/java/index.html
 * http://www.regular-expressions.info/
 */
package sintaticanaliser;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Stack;
import static sintaticanaliser.LexicAnaliser.LEXICAL_NUM;
import static sintaticanaliser.LexicAnaliser.LEXICAL_DELIMITER;
import static sintaticanaliser.LexicAnaliser.END_DELIMITER_TOKEN;
import static sintaticanaliser.LexicAnaliser.LEXICAL_CHAR;
import static sintaticanaliser.LexicAnaliser.LEXICAL_STRING;
import static sintaticanaliser.LexicAnaliser.getIntCode;
import static sintaticanaliser.LexicAnaliser.getFloatCode;
import static sintaticanaliser.LexicAnaliser.getCharCode;
import static sintaticanaliser.LexicAnaliser.getStringCode;
import static sintaticanaliser.State.getLineNumber;
import static sintaticanaliser.SlrLinesItensEnum.*;
import static sintaticanaliser.SlrColumnsEnum.*;
import static sintaticanaliser.State.IS_FUNCTION;
import static sintaticanaliser.State.IS_VARIABLE;
import static sintaticanaliser.State.getConstToTypeMap;
import static sintaticanaliser.State.getFunctionToTypeMap;
import static sintaticanaliser.State.getVariableToTypeMap;
import static sintaticanaliser.State.getIdConst;
import static sintaticanaliser.State.getIdStack;
import static sintaticanaliser.State.whatIsThisId;
import static sintaticanaliser.State.isReadingConst;
import static sintaticanaliser.State.setReadingConst;

/**
 *
 * @author Henrique Colodetti Escanferla GRR20135427
 */
abstract class SintaticAnaliser {
    
    private static final Stack<Integer> valueTypeStack = new Stack<>();
    private static final SlrLinesItensEnum[] stateList = SlrLinesItensEnum.values();
    // list of enum's copy, see typeChecker method
    // value's type codified in integers, see LexicAnaliser.build
    private static final char PERIOD_CHAR = '.'; // const for period's char
    
    /** Defines the full process of analising a code and converting to tokens.
     * 
     * @param args the arguments for main method
     * @see LexicAnaliser
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        State.setStatics(read());
        // transforms "entry.code" into an array of chars to be read
        LexicAnaliser.build();
        // builds states, respective transitions (regex, state)
        // and fill tables of reserved words/types
        int [][] slrTable = buildSlrTable();
        // builds slrTable: a sintatic analysis table SLR(1)
        Stack<Integer> stateStack = new Stack<>(); // stateStack of integers from slrTable
        stateStack.push(0); // push first state, need to go back here in ending process
        String str = null; // to read lexic
        
        for(;;) { // keeps recognizing until lexic error or accept entry
            int itemTable;
            
            if (str == null) { // str null means need to read next lexic
                str = lexicalReader(LexicAnaliser.execute());
                // recognize a token from array of chars and trim that to a substring
            }
            
            itemTable = slrTable[stateStack.peek()][SlrColumnsEnum.findByLexic(str)];
            
            if (itemTable < 0) {
                System.out.println("\nErro sintatico na linha " +
                        getLineNumber());
                // print error and line number where it occured
                System.exit(0); // ends execution
                break; // ends for loop if error
            }
            else {
                typeChecker(itemTable, str); // checks types on some states
                
                if (itemTable <= E111.ordinal()) {
                    stateStack.push(itemTable); // stateStack new state
                    str = null; // cant use same lexic
                }
                else {
                    if (itemTable <= R40.ordinal()) {
                        int i = 0; // iterates in for loop below
                        
                        for(; i < SlrLinesItensEnum.values()[itemTable].getPop(); i++) {
                            stateStack.pop(); // pops getPop() times
                        }
                        
                        itemTable = slrTable[stateStack.peek()]
                                    [SlrLinesItensEnum.values()
                                    [itemTable].getRedSymb()];
                        // read reduction symbol, goes to symbol's column
                        stateStack.push(itemTable); // stateStack new state
                    }
                    else {
                        break; // ends for loop if accept entry
                    }
                }
            }
        }
    }

    /**
     * Reads file entry.code on standard directory putting into a string.
     * @throws IOException
     * @return a string with all the chars decoded from a file "entry.code"
     */
    private static String read() throws IOException {
        String s = "entry.code"; // Filepath to entry.code
        BufferedReader br = new BufferedReader(new FileReader(s));
        StringBuilder sb = new StringBuilder();
        String line = br.readLine(); // read a whole line
        while (line != null) {
            sb.append(line); // append a line
            sb.append(System.lineSeparator()); // append end of previous line with '\n'
            line = br.readLine(); // read next whole line
        }
        if (sb.length() > 0) { sb.deleteCharAt(sb.length() - 1); } // delete last '\n'
        sb.append('\u0000'); // end of string
        String everything = sb.toString();
        br.close(); // closes file "entry.code"
        return everything;
    }
    
    /**
     * Builds slrTable from the SLR(1) table produced by teached algorithm.
     *
     * @return the slrTable
     */
    private static int[][] buildSlrTable() {
        int[][] slrTable = new int[E111.ordinal() + 1][HASHTAG.ordinal() + 1];
        // slr table lines [E0(0) -- E111(111)] and columns [PROG(0) -- HASHTAG(43)]
        
        int i = 0, j;
        for (; i < slrTable.length; i++) {
           for (j = 0; j < slrTable[i].length; j++) {
              slrTable[i][j] = -1; // table starts invalid
           }
        }
        
        // START SLR(1) TABLE
                
        // STATE 0
        slrTable[E0.ordinal()][PROG.ordinal()] = E1.ordinal();
        // [E0][PROG] => [E1]
        slrTable[E0.ordinal()][DECL_VAR.ordinal()] = E107.ordinal();
        // [E0][DECL_VAR] => [E107]
        slrTable[E0.ordinal()][ID.ordinal()] = R38.ordinal();
        // [E0][id] => [R38]
        slrTable[E0.ordinal()][TYPE.ordinal()] = E3.ordinal();
        // [E0][type] => [E3]
        slrTable[E0.ordinal()][T_IF.ordinal()] = R38.ordinal();
        // [E0][if] => [R38]
        slrTable[E0.ordinal()][T_CONST.ordinal()] = R38.ordinal();
        // [E0][const] => [R38]
        slrTable[E0.ordinal()][T_WHILE.ordinal()] = R38.ordinal();
        // [E0][while] => [R38]
        slrTable[E0.ordinal()][T_FOR.ordinal()] = R38.ordinal();
        // [E0][for] => [R38]
        slrTable[E0.ordinal()][FUNCTION.ordinal()] = R38.ordinal();
        // [E0][function] => [R38]
        slrTable[E0.ordinal()][T_MAIN.ordinal()] = R38.ordinal();
        // [E0][main] => [R38]
        // STATE 0
        
        // STATE 1
        slrTable[E1.ordinal()][HASHTAG.ordinal()] = ACEITA.ordinal();
        // [E1][#] => [ACEITA]
        // STATE 1
        
        // STATE 2
        slrTable[E2.ordinal()][HASHTAG.ordinal()] = R1.ordinal();
        // [E2][#] => [R1]
        // STATE 2
        
        // STATE 3
        slrTable[E3.ordinal()][ID.ordinal()] = E4.ordinal();
        // [E3][id] => [E4]
        // STATE 3
        
        // STATE 4
        slrTable[E4.ordinal()][SEMI_COLON.ordinal()] = E5.ordinal();
        // [E4][;] => [E5]
        // STATE 4
        
        // STATE 5
        slrTable[E5.ordinal()][DECL_VAR.ordinal()] = E104.ordinal();
        // [E5][DECL_VAR] => [E104]
        slrTable[E5.ordinal()][ID.ordinal()] = R38.ordinal();
        // [E5][id] => [R38]
        slrTable[E5.ordinal()][TYPE.ordinal()] = E3.ordinal();
        // [E5][type] => [E3]
        slrTable[E5.ordinal()][T_IF.ordinal()] = R38.ordinal();
        // [E5][if] => [R38]
        slrTable[E5.ordinal()][T_CONST.ordinal()] = R38.ordinal();
        // [E5][const] => [R38]
        slrTable[E5.ordinal()][T_WHILE.ordinal()] = R38.ordinal();
        // [E5][while] => [R38]
        slrTable[E5.ordinal()][T_FOR.ordinal()] = R38.ordinal();
        // [E5][for] => [R38]
        slrTable[E5.ordinal()][FUNCTION.ordinal()] = R38.ordinal();
        // [E5][function] => [R38]
        slrTable[E5.ordinal()][T_MAIN.ordinal()] = R38.ordinal();
        // [E5][main] => [R38]
        // STATE 5
        
        // STATE 6
        slrTable[E6.ordinal()][ID.ordinal()] = E7.ordinal();
        // [E6][id] => [E7]
        // STATE 6
        
        // STATE 7
        slrTable[E7.ordinal()][EQUAL.ordinal()] = E8.ordinal();
        // [E7][=] => [E8]
        // STATE 7
        
        // STATE 8
        slrTable[E8.ordinal()][NUM.ordinal()] = E9.ordinal();
        // [E8][num] => [E9]
        // STATE 8
        
        // STATE 9
        slrTable[E9.ordinal()][SEMI_COLON.ordinal()] = E10.ordinal();
        // [E9][;] => [E10]
        // STATE 9
        
        // STATE 10
        slrTable[E10.ordinal()][CONST.ordinal()] = E105.ordinal();
        // [E10][CONST] => [E105]
        slrTable[E10.ordinal()][T_CONST.ordinal()] = E6.ordinal();
        // [E10][const] => [E6]
        slrTable[E10.ordinal()][FUNCTION.ordinal()] = R39.ordinal();
        // [E10][function] => [R39]
        slrTable[E10.ordinal()][T_MAIN.ordinal()] = R39.ordinal();
        // [E10][main] => [R39]
        // STATE 10
        
        // STATE 11
        slrTable[E11.ordinal()][FUNCOES.ordinal()] = E106.ordinal();
        // [E11][FUNCOES] => [E106]
        slrTable[E11.ordinal()][FUNCAO.ordinal()] = E11.ordinal();
        // [E11][FUNCAO] => [E11]
        slrTable[E11.ordinal()][FUNCTION.ordinal()] = E101.ordinal();
        // [E11][function] => [E101]
        slrTable[E11.ordinal()][T_MAIN.ordinal()] = R40.ordinal();
        // [E11][main] => [R40]
        // STATE 11
        
        // STATE 12
        slrTable[E12.ordinal()][R_PARENT.ordinal()] = E13.ordinal();
        // [E12][)] => [E13]
        // STATE 12
        
        // STATE 13
        slrTable[E13.ordinal()][L_BRACE.ordinal()] = E14.ordinal();
        // [E13][{] => [E14]
        // STATE 13
        
        // STATE 14
        slrTable[E14.ordinal()][DECL_VAR.ordinal()] = E110.ordinal();
        // [E14][DECL_VAR] => [E110]
        slrTable[E14.ordinal()][ID.ordinal()] = R38.ordinal();
        // [E14][id] => [R38]
        slrTable[E14.ordinal()][TYPE.ordinal()] = E3.ordinal();
        // [E14][type] => [E3]
        slrTable[E14.ordinal()][T_IF.ordinal()] = R38.ordinal();
        // [E14][if] => [R38]
        slrTable[E14.ordinal()][T_CONST.ordinal()] = R38.ordinal();
        // [E14][const] => [R38]
        slrTable[E14.ordinal()][T_WHILE.ordinal()] = R38.ordinal();
        // [E14][while] => [R38]
        slrTable[E14.ordinal()][T_FOR.ordinal()] = R38.ordinal();
        // [E14][for] => [R38]
        slrTable[E14.ordinal()][FUNCTION.ordinal()] = R38.ordinal();
        // [E14][function] => [R38]
        slrTable[E14.ordinal()][T_MAIN.ordinal()] = R38.ordinal();
        // [E14][main] => [R38]
        // STATE 14
        
        // STATE 15
        slrTable[E15.ordinal()][RETURN.ordinal()] = E16.ordinal();
        // [E15][return] => [E16]
        // STATE 15
        
        // STATE 16
        slrTable[E16.ordinal()][ID.ordinal()] = E17.ordinal();
        // [E16][id] => [E17]
        // STATE 16
        
        // STATE 17
        slrTable[E17.ordinal()][SEMI_COLON.ordinal()] = E18.ordinal();
        // [E17][;] => [E18]
        // STATE 17
        
        // STATE 18
        slrTable[E18.ordinal()][R_BRACE.ordinal()] = E19.ordinal();
        // [E18][}] => [E19]
        // STATE 18
        
        // STATE 19
        slrTable[E19.ordinal()][FUNCTION.ordinal()] = R5.ordinal();
        // [E19][function] => [R5]
        slrTable[E19.ordinal()][T_MAIN.ordinal()] = R5.ordinal();
        // [E19][main] => [R5]
        // STATE 19
        
        // STATE 20
        slrTable[E20.ordinal()][L_BRACE.ordinal()] = E21.ordinal();
        // [E20][{] => [E21]
        // STATE 20
        
        // STATE 21
        slrTable[E21.ordinal()][DECL_VAR.ordinal()] = E111.ordinal();
        // [E21][DECL_VAR] => [E111]
        slrTable[E21.ordinal()][ID.ordinal()] = R38.ordinal();
        // [E21][id] => [R38]
        slrTable[E21.ordinal()][TYPE.ordinal()] = E3.ordinal();
        // [E21][type] => [E3]
        slrTable[E21.ordinal()][T_IF.ordinal()] = R38.ordinal();
        // [E21][if] => [R38]
        slrTable[E21.ordinal()][T_CONST.ordinal()] = R38.ordinal();
        // [E21][const] => [R38]
        slrTable[E21.ordinal()][T_WHILE.ordinal()] = R38.ordinal();
        // [E21][while] => [R38]
        slrTable[E21.ordinal()][T_FOR.ordinal()] = R38.ordinal();
        // [E21][for] => [R38]
        slrTable[E21.ordinal()][FUNCTION.ordinal()] = R38.ordinal();
        // [E21][function] => [R38]
        slrTable[E21.ordinal()][T_MAIN.ordinal()] = R38.ordinal();
        // [E21][main] => [R38]
        // STATE 21
        
        // STATE 22
        slrTable[E22.ordinal()][R_BRACE.ordinal()] = E23.ordinal();
        // [E22][}] => [E23]
        // STATE 22
        
        // STATE 23
        slrTable[E23.ordinal()][HASHTAG.ordinal()] = R6.ordinal();
        // [E23][#] => [R6]
        // STATE 23
        
        // STATE 24
        slrTable[E24.ordinal()][CMDS.ordinal()] = E25.ordinal();
        // [E24][CMDS] => [E25]
        slrTable[E24.ordinal()][CMD.ordinal()] = E24.ordinal();
        // [E24][CMD] => [E24]
        slrTable[E24.ordinal()][IF.ordinal()] = E26.ordinal();
        // [E24][IF] => [E26]
        slrTable[E24.ordinal()][WHILE.ordinal()] = E27.ordinal();
        // [E24][WHILE] => [E27]
        slrTable[E24.ordinal()][FOR.ordinal()] = E28.ordinal();
        // [E24][FOR] => [E28]
        slrTable[E24.ordinal()][ATR.ordinal()] = E29.ordinal();
        // [E24][ATR] => [E29]
        slrTable[E24.ordinal()][CH_FUNC.ordinal()] = E30.ordinal();
        // [E24][CH_FUNC] => [E30]
        slrTable[E24.ordinal()][INCR.ordinal()] = E31.ordinal();
        // [E24][INCR] => [E31]
        slrTable[E24.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E24][id] => [E64]
        slrTable[E24.ordinal()][T_IF.ordinal()] = E33.ordinal();
        // [E24][if] => [E33]
        slrTable[E24.ordinal()][T_WHILE.ordinal()] = E45.ordinal();
        // [E24][while] => [E45]
        slrTable[E24.ordinal()][T_FOR.ordinal()] = E53.ordinal();
        // [E24][for] => [E53]
        slrTable[E24.ordinal()][RETURN.ordinal()] = R8.ordinal();
        // [E24][return] => [R8]
        slrTable[E24.ordinal()][R_BRACE.ordinal()] = R8.ordinal();
        // [E24][}] => [R8]
        // STATE 24
        
        // STATE 25
        slrTable[E25.ordinal()][RETURN.ordinal()] = R7.ordinal();
        // [E25][return] => [R7]
        slrTable[E25.ordinal()][R_BRACE.ordinal()] = R7.ordinal();
        // [E25][}] => [R7]
        // STATE 25
        
        // STATE 26
        slrTable[E26.ordinal()][ID.ordinal()] = R9.ordinal();
        // [E26][id] => [R9]
        slrTable[E26.ordinal()][T_IF.ordinal()] = R9.ordinal();
        // [E26][if] => [R9]
        slrTable[E26.ordinal()][T_WHILE.ordinal()] = R9.ordinal();
        // [E26][while] => [R9]
        slrTable[E26.ordinal()][T_FOR.ordinal()] = R9.ordinal();
        // [E26][for] => [R9]
        slrTable[E26.ordinal()][RETURN.ordinal()] = R9.ordinal();
        // [E26][return] => [R9]
        slrTable[E26.ordinal()][R_BRACE.ordinal()] = R9.ordinal();
        // [E26][}] => [R9]
        // STATE 26
        
        // STATE 27
        slrTable[E27.ordinal()][ID.ordinal()] = R10.ordinal();
        // [E27][id] => [R10]
        slrTable[E27.ordinal()][T_IF.ordinal()] = R10.ordinal();
        // [E27][if] => [R10]
        slrTable[E27.ordinal()][T_WHILE.ordinal()] = R10.ordinal();
        // [E27][while] => [R10]
        slrTable[E27.ordinal()][T_FOR.ordinal()] = R10.ordinal();
        // [E27][for] => [R10]
        slrTable[E27.ordinal()][RETURN.ordinal()] = R10.ordinal();
        // [E27][return] => [R10]
        slrTable[E27.ordinal()][R_BRACE.ordinal()] = R10.ordinal();
        // [E27][}] => [R10]
        // STATE 27
        
        // STATE 28
        slrTable[E28.ordinal()][ID.ordinal()] = R11.ordinal();
        // [E28][id] => [R11]
        slrTable[E28.ordinal()][T_IF.ordinal()] = R11.ordinal();
        // [E28][if] => [R11]
        slrTable[E28.ordinal()][T_WHILE.ordinal()] = R11.ordinal();
        // [E28][while] => [R11]
        slrTable[E28.ordinal()][T_FOR.ordinal()] = R11.ordinal();
        // [E28][for] => [R11]
        slrTable[E28.ordinal()][RETURN.ordinal()] = R11.ordinal();
        // [E28][return] => [R11]
        slrTable[E28.ordinal()][R_BRACE.ordinal()] = R11.ordinal();
        // [E28][}] => [R11]
        // STATE 28
        
        // STATE 29
        slrTable[E29.ordinal()][ID.ordinal()] = R12.ordinal();
        // [E29][id] => [R12]
        slrTable[E29.ordinal()][T_IF.ordinal()] = R12.ordinal();
        // [E29][if] => [R12]
        slrTable[E29.ordinal()][T_WHILE.ordinal()] = R12.ordinal();
        // [E29][while] => [R12]
        slrTable[E29.ordinal()][T_FOR.ordinal()] = R12.ordinal();
        // [E29][for] => [R12]
        slrTable[E29.ordinal()][RETURN.ordinal()] = R12.ordinal();
        // [E29][return] => [R12]
        slrTable[E29.ordinal()][R_BRACE.ordinal()] = R12.ordinal();
        // [E29][}] => [R12]
        // STATE 29
        
        // STATE 30
        slrTable[E30.ordinal()][ID.ordinal()] = R13.ordinal();
        // [E30][id] => [R13]
        slrTable[E30.ordinal()][T_IF.ordinal()] = R13.ordinal();
        // [E30][if] => [R13]
        slrTable[E30.ordinal()][T_WHILE.ordinal()] = R13.ordinal();
        // [E30][while] => [R13]
        slrTable[E30.ordinal()][T_FOR.ordinal()] = R13.ordinal();
        // [E30][for] => [R13]
        slrTable[E30.ordinal()][RETURN.ordinal()] = R13.ordinal();
        // [E30][return] => [R13]
        slrTable[E30.ordinal()][R_BRACE.ordinal()] = R13.ordinal();
        // [E30][}] => [R13]
        // STATE 30
        
        // STATE 31
        slrTable[E31.ordinal()][SEMI_COLON.ordinal()] = E32.ordinal();
        // [E31][;] => [E32]
        // STATE 31
        
        // STATE 32
        slrTable[E32.ordinal()][ID.ordinal()] = R14.ordinal();
        // [E32][id] => [R14]
        slrTable[E32.ordinal()][T_IF.ordinal()] = R14.ordinal();
        // [E32][if] => [R14]
        slrTable[E32.ordinal()][T_WHILE.ordinal()] = R14.ordinal();
        // [E32][while] => [R14]
        slrTable[E32.ordinal()][T_FOR.ordinal()] = R14.ordinal();
        // [E32][for] => [R14]
        slrTable[E32.ordinal()][RETURN.ordinal()] = R14.ordinal();
        // [E32][return] => [R14]
        slrTable[E32.ordinal()][R_BRACE.ordinal()] = R14.ordinal();
        // [E32][}] => [R14]
        // STATE 32
        
        // STATE 33
        slrTable[E33.ordinal()][L_PARENT.ordinal()] = E34.ordinal();
        // [E33][(] => [E34]
        // STATE 33
        
        // STATE 34
        slrTable[E34.ordinal()][TESTE.ordinal()] = E35.ordinal();
        // [E34][TESTE] => [E35]
        slrTable[E34.ordinal()][EXPR_REL.ordinal()] = E90.ordinal();
        // [E34][EXPR_REL] => [E90]
        slrTable[E34.ordinal()][NUM.ordinal()] = E93.ordinal();
        // [E34][num] => [E93]
        slrTable[E34.ordinal()][ID.ordinal()] = E97.ordinal();
        // [E34][id] => [E97]
        // STATE 34
        
        // STATE 35
        slrTable[E35.ordinal()][R_PARENT.ordinal()] = E36.ordinal();
        // [E35][)] => [E36]
        // STATE 35
        
        // STATE 36
        slrTable[E36.ordinal()][THEN.ordinal()] = E37.ordinal();
        // [E36][then] => [E37]
        // STATE 36
        
        // STATE 37
        slrTable[E37.ordinal()][L_BRACE.ordinal()] = E38.ordinal();
        // [E37][{] => [E38]
        // STATE 37
        
        // STATE 38
        slrTable[E38.ordinal()][CMDS.ordinal()] = E39.ordinal();
        // [E38][CMDS] => [E39]
        slrTable[E38.ordinal()][CMD.ordinal()] = E24.ordinal();
        // [E38][CMD] => [E24]
        slrTable[E38.ordinal()][IF.ordinal()] = E26.ordinal();
        // [E38][IF] => [E26]
        slrTable[E38.ordinal()][WHILE.ordinal()] = E27.ordinal();
        // [E38][WHILE] => [E27]
        slrTable[E38.ordinal()][FOR.ordinal()] = E28.ordinal();
        // [E38][FOR] => [E28]
        slrTable[E38.ordinal()][ATR.ordinal()] = E29.ordinal();
        // [E38][ATR] => [E29]
        slrTable[E38.ordinal()][CH_FUNC.ordinal()] = E30.ordinal();
        // [E38][CH_FUNC] => [E30]
        slrTable[E38.ordinal()][INCR.ordinal()] = E31.ordinal();
        // [E38][INCR] => [E31]
        slrTable[E38.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E38][id] => [E64]
        slrTable[E38.ordinal()][T_IF.ordinal()] = E33.ordinal();
        // [E38][if] => [E33]
        slrTable[E38.ordinal()][T_WHILE.ordinal()] = E45.ordinal();
        // [E38][while] => [E45]
        slrTable[E38.ordinal()][T_FOR.ordinal()] = E53.ordinal();
        // [E38][for] => [E53]
        // STATE 38
        
        // STATE 39
        slrTable[E39.ordinal()][R_BRACE.ordinal()] = E40.ordinal();
        // [E39][}] => [E40]
        // STATE 39
        
        // STATE 40
        slrTable[E40.ordinal()][ID.ordinal()] = R15.ordinal();
        // [E40][id] => [R15]
        slrTable[E40.ordinal()][T_IF.ordinal()] = R15.ordinal();
        // [E40][if] => [R15]
        slrTable[E40.ordinal()][ELSE.ordinal()] = E41.ordinal();
        // [E40][else] => [E41]
        slrTable[E40.ordinal()][T_WHILE.ordinal()] = R15.ordinal();
        // [E40][while] => [R15]
        slrTable[E40.ordinal()][T_FOR.ordinal()] = R15.ordinal();
        // [E40][for] => [R15]
        slrTable[E40.ordinal()][RETURN.ordinal()] = R15.ordinal();
        // [E40][return] => [R15]
        slrTable[E40.ordinal()][R_BRACE.ordinal()] = R15.ordinal();
        // [E40][}] => [R15]
        // STATE 40
        
        // STATE 41
        slrTable[E41.ordinal()][L_BRACE.ordinal()] = E42.ordinal();
        // [E41][{] => [E42]
        // STATE 41
        
        // STATE 42
        slrTable[E42.ordinal()][CMDS.ordinal()] = E43.ordinal();
        // [E42][CMDS] => [E43]
        slrTable[E42.ordinal()][CMD.ordinal()] = E24.ordinal();
        // [E42][CMD] => [E24]
        slrTable[E42.ordinal()][IF.ordinal()] = E26.ordinal();
        // [E42][IF] => [E26]
        slrTable[E42.ordinal()][WHILE.ordinal()] = E27.ordinal();
        // [E42][WHILE] => [E27]
        slrTable[E42.ordinal()][FOR.ordinal()] = E28.ordinal();
        // [E42][FOR] => [E28]
        slrTable[E42.ordinal()][ATR.ordinal()] = E29.ordinal();
        // [E42][ATR] => [E29]
        slrTable[E42.ordinal()][CH_FUNC.ordinal()] = E30.ordinal();
        // [E42][CH_FUNC] => [E30]
        slrTable[E42.ordinal()][INCR.ordinal()] = E31.ordinal();
        // [E42][INCR] => [E31]
        slrTable[E42.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E42][id] => [E64]
        slrTable[E42.ordinal()][T_IF.ordinal()] = E33.ordinal();
        // [E42][if] => [E33]
        slrTable[E42.ordinal()][T_WHILE.ordinal()] = E45.ordinal();
        // [E42][while] => [E45]
        slrTable[E42.ordinal()][T_FOR.ordinal()] = E53.ordinal();
        // [E42][for] => [E53]
        // STATE 42
        
        // STATE 43
        slrTable[E43.ordinal()][R_BRACE.ordinal()] = E44.ordinal();
        // [E43][}] => [E44]
        // STATE 43
        
        // STATE 44
        slrTable[E44.ordinal()][ID.ordinal()] = R16.ordinal();
        // [E44][id] => [R16]
        slrTable[E44.ordinal()][T_IF.ordinal()] = R16.ordinal();
        // [E44][if] => [R16]
        slrTable[E44.ordinal()][T_WHILE.ordinal()] = R16.ordinal();
        // [E44][while] => [R16]
        slrTable[E44.ordinal()][T_FOR.ordinal()] = R16.ordinal();
        // [E44][for] => [R16]
        slrTable[E44.ordinal()][RETURN.ordinal()] = R16.ordinal();
        // [E44][return] => [R16]
        slrTable[E44.ordinal()][R_BRACE.ordinal()] = R16.ordinal();
        // [E44][}] => [R16]
        // STATE 44
        
        // STATE 45
        slrTable[E45.ordinal()][L_PARENT.ordinal()] = E46.ordinal();
        // [E45][(] => [E46]
        // STATE 45
        
        // STATE 46
        slrTable[E46.ordinal()][TESTE.ordinal()] = E47.ordinal();
        // [E46][TESTE] => [E47]
        slrTable[E46.ordinal()][EXPR_REL.ordinal()] = E90.ordinal();
        // [E46][EXPR_REL] => [E90]
        slrTable[E46.ordinal()][NUM.ordinal()] = E93.ordinal();
        // [E46][num] => [E93]
        slrTable[E46.ordinal()][ID.ordinal()] = E97.ordinal();
        // [E46][id] => [E97]
        // STATE 46
        
        // STATE 47
        slrTable[E47.ordinal()][R_PARENT.ordinal()] = E48.ordinal();
        // [E47][)] => [E48]
        // STATE 47
        
        // STATE 48
        slrTable[E48.ordinal()][DO.ordinal()] = E49.ordinal();
        // [E48][do] => [E49]
        // STATE 48
        
        // STATE 49
        slrTable[E49.ordinal()][L_BRACE.ordinal()] = E50.ordinal();
        // [E49][{] => [E50]
        // STATE 49
        
        // STATE 50
        slrTable[E50.ordinal()][CMDS.ordinal()] = E51.ordinal();
        // [E50][CMDS] => [E51]
        slrTable[E50.ordinal()][CMD.ordinal()] = E24.ordinal();
        // [E50][CMD] => [E24]
        slrTable[E50.ordinal()][IF.ordinal()] = E26.ordinal();
        // [E50][IF] => [E26]
        slrTable[E50.ordinal()][WHILE.ordinal()] = E27.ordinal();
        // [E50][WHILE] => [E27]
        slrTable[E50.ordinal()][FOR.ordinal()] = E28.ordinal();
        // [E50][FOR] => [E28]
        slrTable[E50.ordinal()][ATR.ordinal()] = E29.ordinal();
        // [E50][ATR] => [E29]
        slrTable[E50.ordinal()][CH_FUNC.ordinal()] = E30.ordinal();
        // [E50][CH_FUNC] => [E30]
        slrTable[E50.ordinal()][INCR.ordinal()] = E31.ordinal();
        // [E50][INCR] => [E31]
        slrTable[E50.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E50][id] => [E64]
        slrTable[E50.ordinal()][T_IF.ordinal()] = E33.ordinal();
        // [E50][if] => [E33]
        slrTable[E50.ordinal()][T_WHILE.ordinal()] = E45.ordinal();
        // [E50][while] => [E45]
        slrTable[E50.ordinal()][T_FOR.ordinal()] = E53.ordinal();
        // [E50][for] => [E53]
        // STATE 50
        
        // STATE 51
        slrTable[E51.ordinal()][R_BRACE.ordinal()] = E52.ordinal();
        // [E51][}] => [E52]
        // STATE 51
        
        // STATE 52
        slrTable[E52.ordinal()][ID.ordinal()] = R17.ordinal();
        // [E52][id] => [R17]
        slrTable[E52.ordinal()][T_IF.ordinal()] = R17.ordinal();
        // [E52][if] => [R17]
        slrTable[E52.ordinal()][T_WHILE.ordinal()] = R17.ordinal();
        // [E52][while] => [R17]
        slrTable[E52.ordinal()][T_FOR.ordinal()] = R17.ordinal();
        // [E52][for] => [R17]
        slrTable[E52.ordinal()][RETURN.ordinal()] = R17.ordinal();
        // [E52][return] => [R17]
        slrTable[E52.ordinal()][R_BRACE.ordinal()] = R17.ordinal();
        // [E52][}] => [R17]
        // STATE 52
        
        // STATE 53
        slrTable[E53.ordinal()][L_PARENT.ordinal()] = E54.ordinal();
        // [E53][(] => [E54]
        // STATE 53
        
        // STATE 54
        slrTable[E54.ordinal()][ATR_FOR.ordinal()] = E55.ordinal();
        // [E54][ATR_FOR] => [E55]
        slrTable[E54.ordinal()][ID.ordinal()] = E81.ordinal();
        // [E54][id] => [E81]
        // STATE 54
        
        // STATE 55
        slrTable[E55.ordinal()][SEMI_COLON.ordinal()] = E56.ordinal();
        // [E55][;] => [E56]
        // STATE 55
        
        // STATE 56
        slrTable[E56.ordinal()][TESTE.ordinal()] = E57.ordinal();
        // [E56][TESTE] => [E47]
        slrTable[E56.ordinal()][EXPR_REL.ordinal()] = E90.ordinal();
        // [E56][EXPR_REL] => [E90]
        slrTable[E56.ordinal()][NUM.ordinal()] = E93.ordinal();
        // [E56][num] => [E93]
        slrTable[E56.ordinal()][ID.ordinal()] = E97.ordinal();
        // [E56][id] => [E97]
        // STATE 56
        
        // STATE 57
        slrTable[E57.ordinal()][SEMI_COLON.ordinal()] = E58.ordinal();
        // [E57][;] => [E58]
        // STATE 57
        
        // STATE 58
        slrTable[E58.ordinal()][INCR.ordinal()] = E59.ordinal();
        // [E58][INCR] => [E59]
        slrTable[E58.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E58][id] => [E64]
        // STATE 58
        
        // STATE 59
        slrTable[E59.ordinal()][R_PARENT.ordinal()] = E60.ordinal();
        // [E59][)] => [E60]
        // STATE 59
        
        // STATE 60
        slrTable[E60.ordinal()][L_BRACE.ordinal()] = E61.ordinal();
        // [E60][{] => [E61]
        // STATE 60
        
        // STATE 61
        slrTable[E61.ordinal()][CMDS.ordinal()] = E62.ordinal();
        // [E61][CMDS] => [E62]
        slrTable[E61.ordinal()][CMD.ordinal()] = E24.ordinal();
        // [E61][CMD] => [E24]
        slrTable[E61.ordinal()][IF.ordinal()] = E26.ordinal();
        // [E61][IF] => [E26]
        slrTable[E61.ordinal()][WHILE.ordinal()] = E27.ordinal();
        // [E61][WHILE] => [E27]
        slrTable[E61.ordinal()][FOR.ordinal()] = E28.ordinal();
        // [E61][FOR] => [E28]
        slrTable[E61.ordinal()][ATR.ordinal()] = E29.ordinal();
        // [E61][ATR] => [E29]
        slrTable[E61.ordinal()][CH_FUNC.ordinal()] = E30.ordinal();
        // [E61][CH_FUNC] => [E30]
        slrTable[E61.ordinal()][INCR.ordinal()] = E31.ordinal();
        // [E61][INCR] => [E31]
        slrTable[E61.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E61][id] => [E64]
        slrTable[E61.ordinal()][T_IF.ordinal()] = E33.ordinal();
        // [E61][if] => [E33]
        slrTable[E61.ordinal()][T_WHILE.ordinal()] = E45.ordinal();
        // [E61][while] => [E45]
        slrTable[E61.ordinal()][T_FOR.ordinal()] = E53.ordinal();
        // [E61][for] => [E53]
        // STATE 61
        
        // STATE 62
        slrTable[E62.ordinal()][R_BRACE.ordinal()] = E63.ordinal();
        // [E62][}] => [E63]
        // STATE 62
        
        // STATE 63
        slrTable[E63.ordinal()][ID.ordinal()] = R18.ordinal();
        // [E63][id] => [R18]
        slrTable[E63.ordinal()][T_IF.ordinal()] = R18.ordinal();
        // [E63][if] => [R18]
        slrTable[E63.ordinal()][T_WHILE.ordinal()] = R18.ordinal();
        // [E63][while] => [R18]
        slrTable[E63.ordinal()][T_FOR.ordinal()] = R18.ordinal();
        // [E63][for] => [R18]
        slrTable[E63.ordinal()][RETURN.ordinal()] = R18.ordinal();
        // [E63][return] => [R18]
        slrTable[E63.ordinal()][R_BRACE.ordinal()] = R18.ordinal();
        // [E63][}] => [R18]
        // STATE 63
        
        // STATE 64
        slrTable[E64.ordinal()][INC.ordinal()] = E80.ordinal();
        // [E64][inc] => [E80]
        slrTable[E64.ordinal()][L_PARENT.ordinal()] = E77.ordinal();
        // [E64][(] => [E77]
        slrTable[E64.ordinal()][EQUAL.ordinal()] = E65.ordinal();
        // [E64][=] => [E65]
        // STATE 64
        
        // STATE 65
        slrTable[E65.ordinal()][CH_FUNC.ordinal()] = E74.ordinal();
        // [E65][CH_FUNC] => [E74]
        slrTable[E65.ordinal()][EXPR_MAT.ordinal()] = E68.ordinal();
        // [E65][EXPR_MAT] => [E68]
        slrTable[E65.ordinal()][STR.ordinal()] = E72.ordinal();
        // [E65][str] => [E72]
        slrTable[E65.ordinal()][CH.ordinal()] = E70.ordinal();
        // [E65][ch] => [E70]
        slrTable[E65.ordinal()][NUM.ordinal()] = E66.ordinal();
        // [E65][num] => [E66]
        slrTable[E65.ordinal()][ID.ordinal()] = E75.ordinal();
        // [E65][id] => [E75]
        // STATE 65
        
        // STATE 66
        slrTable[E66.ordinal()][OP_ART.ordinal()] = E84.ordinal();
        // [E66][op_art] => [E84]
        slrTable[E66.ordinal()][SEMI_COLON.ordinal()] = E67.ordinal();
        // [E66][;] => [E67]
        // STATE 66
        
        // STATE 67
        slrTable[E67.ordinal()][ID.ordinal()] = R19.ordinal();
        // [E67][id] => [R19]
        slrTable[E67.ordinal()][T_IF.ordinal()] = R19.ordinal();
        // [E67][if] => [R19]
        slrTable[E67.ordinal()][T_WHILE.ordinal()] = R19.ordinal();
        // [E67][while] => [R19]
        slrTable[E67.ordinal()][T_FOR.ordinal()] = R19.ordinal();
        // [E67][for] => [R19]
        slrTable[E67.ordinal()][RETURN.ordinal()] = R19.ordinal();
        // [E67][return] => [R19]
        slrTable[E67.ordinal()][R_BRACE.ordinal()] = R19.ordinal();
        // [E67][}] => [R19]
        // STATE 67
        
        // STATE 68
        slrTable[E68.ordinal()][SEMI_COLON.ordinal()] = E69.ordinal();
        // [E68][;] => [E69]
        // STATE 68
        
        // STATE 69
        slrTable[E69.ordinal()][ID.ordinal()] = R20.ordinal();
        // [E69][id] => [R20]
        slrTable[E69.ordinal()][T_IF.ordinal()] = R20.ordinal();
        // [E69][if] => [R20]
        slrTable[E69.ordinal()][T_WHILE.ordinal()] = R20.ordinal();
        // [E69][while] => [R20]
        slrTable[E69.ordinal()][T_FOR.ordinal()] = R20.ordinal();
        // [E69][for] => [R20]
        slrTable[E69.ordinal()][RETURN.ordinal()] = R20.ordinal();
        // [E69][return] => [R20]
        slrTable[E69.ordinal()][R_BRACE.ordinal()] = R20.ordinal();
        // [E69][}] => [R20]
        // STATE 69
        
        // STATE 70
        slrTable[E70.ordinal()][SEMI_COLON.ordinal()] = E71.ordinal();
        // [E70][;] => [E71]
        // STATE 70
        
        // STATE 71
        slrTable[E71.ordinal()][ID.ordinal()] = R21.ordinal();
        // [E71][id] => [R21]
        slrTable[E71.ordinal()][T_IF.ordinal()] = R21.ordinal();
        // [E71][if] => [R21]
        slrTable[E71.ordinal()][T_WHILE.ordinal()] = R21.ordinal();
        // [E71][while] => [R21]
        slrTable[E71.ordinal()][T_FOR.ordinal()] = R21.ordinal();
        // [E71][for] => [R21]
        slrTable[E71.ordinal()][RETURN.ordinal()] = R21.ordinal();
        // [E71][return] => [R21]
        slrTable[E71.ordinal()][R_BRACE.ordinal()] = R21.ordinal();
        // [E71][}] => [R21]
        // STATE 71
        
        // STATE 72
        slrTable[E72.ordinal()][SEMI_COLON.ordinal()] = E73.ordinal();
        // [E72][;] => [E73]
        // STATE 72
        
        // STATE 73
        slrTable[E73.ordinal()][ID.ordinal()] = R22.ordinal();
        // [E73][id] => [R22]
        slrTable[E73.ordinal()][T_IF.ordinal()] = R22.ordinal();
        // [E73][if] => [R22]
        slrTable[E73.ordinal()][T_WHILE.ordinal()] = R22.ordinal();
        // [E73][while] => [R22]
        slrTable[E73.ordinal()][T_FOR.ordinal()] = R22.ordinal();
        // [E73][for] => [R22]
        slrTable[E73.ordinal()][RETURN.ordinal()] = R22.ordinal();
        // [E73][return] => [R22]
        slrTable[E73.ordinal()][R_BRACE.ordinal()] = R22.ordinal();
        // [E73][}] => [R22]
        // STATE 73
        
        // STATE 74
        slrTable[E74.ordinal()][ID.ordinal()] = R23.ordinal();
        // [E74][id] => [R23]
        slrTable[E74.ordinal()][T_IF.ordinal()] = R23.ordinal();
        // [E74][if] => [R23]
        slrTable[E74.ordinal()][T_WHILE.ordinal()] = R23.ordinal();
        // [E74][while] => [R23]
        slrTable[E74.ordinal()][T_FOR.ordinal()] = R23.ordinal();
        // [E74][for] => [R23]
        slrTable[E74.ordinal()][RETURN.ordinal()] = R23.ordinal();
        // [E74][return] => [R23]
        slrTable[E74.ordinal()][R_BRACE.ordinal()] = R23.ordinal();
        // [E74][}] => [R23]
        // STATE 74
        
        // STATE 75
        slrTable[E75.ordinal()][OP_ART.ordinal()] = E87.ordinal();
        // [E75][op_art] => [E87]
        slrTable[E75.ordinal()][SEMI_COLON.ordinal()] = E76.ordinal();
        // [E75][;] => [E76]
        slrTable[E75.ordinal()][L_PARENT.ordinal()] = E77.ordinal();
        // [E75][(] => [E77]
        // STATE 75
        
        // STATE 76
        slrTable[E76.ordinal()][ID.ordinal()] = R24.ordinal();
        // [E76][id] => [R24]
        slrTable[E76.ordinal()][T_IF.ordinal()] = R24.ordinal();
        // [E76][if] => [R24]
        slrTable[E76.ordinal()][T_WHILE.ordinal()] = R24.ordinal();
        // [E76][while] => [R24]
        slrTable[E76.ordinal()][T_FOR.ordinal()] = R24.ordinal();
        // [E76][for] => [R24]
        slrTable[E76.ordinal()][RETURN.ordinal()] = R24.ordinal();
        // [E76][return] => [R24]
        slrTable[E76.ordinal()][R_BRACE.ordinal()] = R24.ordinal();
        // [E76][}] => [R24]
        // STATE 76
        
        // STATE 77
        slrTable[E77.ordinal()][R_PARENT.ordinal()] = E78.ordinal();
        // [E77][)] => [E78]
        // STATE 77
        
        // STATE 78
        slrTable[E78.ordinal()][SEMI_COLON.ordinal()] = E79.ordinal();
        // [E78][;] => [E79]
        // STATE 78
        
        // STATE 79
        slrTable[E79.ordinal()][ID.ordinal()] = R25.ordinal();
        // [E79][id] => [R25]
        slrTable[E79.ordinal()][T_IF.ordinal()] = R25.ordinal();
        // [E79][if] => [R25]
        slrTable[E79.ordinal()][T_WHILE.ordinal()] = R25.ordinal();
        // [E79][while] => [R25]
        slrTable[E79.ordinal()][T_FOR.ordinal()] = R25.ordinal();
        // [E79][for] => [R25]
        slrTable[E79.ordinal()][RETURN.ordinal()] = R25.ordinal();
        // [E79][return] => [R25]
        slrTable[E79.ordinal()][R_BRACE.ordinal()] = R25.ordinal();
        // [E79][}] => [R25]
        // STATE 79
        
        // STATE 80
        slrTable[E80.ordinal()][SEMI_COLON.ordinal()] = R26.ordinal();
        // [E80][;] => [R26]
        slrTable[E80.ordinal()][R_PARENT.ordinal()] = R26.ordinal();
        // [E80][)] => [R26]
        // STATE 80
        
        // STATE 81
        slrTable[E81.ordinal()][EQUAL.ordinal()] = E82.ordinal();
        // [E81][=] => [E82]
        // STATE 81
        
        // STATE 82
        slrTable[E82.ordinal()][NUM.ordinal()] = E83.ordinal();
        // [E82][num] => [E83]
        // STATE 82
        
        // STATE 83
        slrTable[E83.ordinal()][SEMI_COLON.ordinal()] = R27.ordinal();
        // [E83][;] => [R27]
        // STATE 83
        
        // STATE 84
        slrTable[E84.ordinal()][NUM.ordinal()] = E85.ordinal();
        // [E84][num] => [E85]
        slrTable[E84.ordinal()][ID.ordinal()] = E86.ordinal();
        // [E84][id] => [E86]
        // STATE 84
        
        // STATE 85
        slrTable[E85.ordinal()][SEMI_COLON.ordinal()] = R28.ordinal();
        // [E85][;] => [R28]
        // STATE 85
        
        // STATE 86
        slrTable[E86.ordinal()][SEMI_COLON.ordinal()] = R31.ordinal();
        // [E86][;] => [R31]
        // STATE 86
        
        // STATE 87
        slrTable[E87.ordinal()][NUM.ordinal()] = E88.ordinal();
        // [E87][num] => [E88]
        slrTable[E87.ordinal()][ID.ordinal()] = E89.ordinal();
        // [E87][id] => [E89]
        // STATE 87
        
        // STATE 88
        slrTable[E88.ordinal()][SEMI_COLON.ordinal()] = R30.ordinal();
        // [E88][;] => [R30]
        // STATE 88
        
        // STATE 89
        slrTable[E89.ordinal()][SEMI_COLON.ordinal()] = R29.ordinal();
        // [E89][;] => [R29]
        // STATE 89
        
        // STATE 90
        slrTable[E90.ordinal()][OP_LOG.ordinal()] = E91.ordinal();
        // [E90][op_log] => [E91]
        slrTable[E90.ordinal()][SEMI_COLON.ordinal()] = R32.ordinal();
        // [E90][;] => [R32]
        slrTable[E90.ordinal()][R_PARENT.ordinal()] = R32.ordinal();
        // [E90][)] => [R32]
        // STATE 90
        
        // STATE 91
        slrTable[E91.ordinal()][TESTE.ordinal()] = E92.ordinal();
        // [E91][TESTE] => [E92]
        slrTable[E91.ordinal()][EXPR_REL.ordinal()] = E90.ordinal();
        // [E91][EXPR_REL] => [E90]
        slrTable[E91.ordinal()][NUM.ordinal()] = E93.ordinal();
        // [E91][num] => [E93]
        slrTable[E91.ordinal()][ID.ordinal()] = E97.ordinal();
        // [E91]id] => [E97]
        // STATE 91
        
        // STATE 92
        slrTable[E92.ordinal()][SEMI_COLON.ordinal()] = R33.ordinal();
        // [E92][;] => [R33]
        slrTable[E92.ordinal()][R_PARENT.ordinal()] = R33.ordinal();
        // [E92][)] => [R33]
        // STATE 92
        
        // STATE 93
        slrTable[E93.ordinal()][OP_REL.ordinal()] = E94.ordinal();
        // [E93][op_rel] => [E94]
        // STATE 93
        
        // STATE 94
        slrTable[E94.ordinal()][NUM.ordinal()] = E95.ordinal();
        // [E94][num] => [E95]
        slrTable[E94.ordinal()][ID.ordinal()] = E96.ordinal();
        // [E94][id] => [E96]
        // STATE 94
        
        // STATE 95
        slrTable[E95.ordinal()][OP_LOG.ordinal()] = R34.ordinal();
        // [E95][op_log] => [R34]
        slrTable[E95.ordinal()][SEMI_COLON.ordinal()] = R34.ordinal();
        // [E95][;] => [R34]
        slrTable[E95.ordinal()][R_PARENT.ordinal()] = R34.ordinal();
        // [E95][)] => [R34]
        // STATE 95
        
        // STATE 96
        slrTable[E96.ordinal()][OP_LOG.ordinal()] = R37.ordinal();
        // [E96][op_log] => [R37]
        slrTable[E96.ordinal()][SEMI_COLON.ordinal()] = R37.ordinal();
        // [E96][;] => [R37]
        slrTable[E96.ordinal()][R_PARENT.ordinal()] = R37.ordinal();
        // [E96][)] => [R37]
        // STATE 96
        
        // STATE 97
        slrTable[E97.ordinal()][OP_REL.ordinal()] = E98.ordinal();
        // [E97][op_rel] => [E98]
        // STATE 97
        
        // STATE 98
        slrTable[E98.ordinal()][NUM.ordinal()] = E99.ordinal();
        // [E98][num] => [E99]
        slrTable[E98.ordinal()][ID.ordinal()] = E100.ordinal();
        // [E98][id] => [E100]
        // STATE 98
        
        // STATE 99
        slrTable[E99.ordinal()][OP_LOG.ordinal()] = R36.ordinal();
        // [E99][op_log] => [R36]
        slrTable[E99.ordinal()][SEMI_COLON.ordinal()] = R36.ordinal();
        // [E99][;] => [R36]
        slrTable[E99.ordinal()][R_PARENT.ordinal()] = R36.ordinal();
        // [E99][)] => [R36]
        // STATE 99
        
        // STATE 100
        slrTable[E100.ordinal()][OP_LOG.ordinal()] = R35.ordinal();
        // [E100][op_log] => [R35]
        slrTable[E100.ordinal()][SEMI_COLON.ordinal()] = R35.ordinal();
        // [E100][;] => [R35]
        slrTable[E100.ordinal()][R_PARENT.ordinal()] = R35.ordinal();
        // [E100][)] => [R35]
        // STATE 100
        
        // STATE 101
        slrTable[E101.ordinal()][TYPE.ordinal()] = E102.ordinal();
        // [E101][type] => [E102]
        // STATE 101
        
        // STATE 102
        slrTable[E102.ordinal()][ID.ordinal()] = E103.ordinal();
        // [E102][id] => [E103]
        // STATE 102
        
        // STATE 103
        slrTable[E103.ordinal()][L_PARENT.ordinal()] = E12.ordinal();
        // [E103][(] => [E12]
        // STATE 103
        
        // STATE 104
        slrTable[E104.ordinal()][ID.ordinal()] = R2.ordinal();
        // [E104][id] => [R2]
        slrTable[E104.ordinal()][T_IF.ordinal()] = R2.ordinal();
        // [E104][if] => [R2]
        slrTable[E104.ordinal()][T_CONST.ordinal()] = R2.ordinal();
        // [E104][const] => [R2]
        slrTable[E104.ordinal()][T_WHILE.ordinal()] = R2.ordinal();
        // [E104][while] => [R2]
        slrTable[E104.ordinal()][T_FOR.ordinal()] = R2.ordinal();
        // [E104][for] => [R2]
        slrTable[E104.ordinal()][FUNCTION.ordinal()] = R2.ordinal();
        // [E104][function] => [R2]
        slrTable[E104.ordinal()][T_MAIN.ordinal()] = R2.ordinal();
        // [E104][main] => [R2]
        // STATE 104
        
        // STATE 105
        slrTable[E105.ordinal()][FUNCTION.ordinal()] = R3.ordinal();
        // [E105][function] => [R3]
        slrTable[E105.ordinal()][T_MAIN.ordinal()] = R3.ordinal();
        // [E105][main] => [R3]
        // STATE 105
        
        // STATE 106
        slrTable[E106.ordinal()][T_MAIN.ordinal()] = R4.ordinal();
        // [E106][main] => [R4]
        // STATE 106
        
        // STATE 107
        slrTable[E107.ordinal()][CONST.ordinal()] = E108.ordinal();
        // [E107][CONST] => [E108]
        slrTable[E107.ordinal()][T_CONST.ordinal()] = E6.ordinal();
        // [E107][const] => [E6]
        slrTable[E107.ordinal()][FUNCTION.ordinal()] = R39.ordinal();
        // [E107][function] => [R39]
        slrTable[E107.ordinal()][T_MAIN.ordinal()] = R39.ordinal();
        // [E107][main] => [R39]
        // STATE 107
        
        // STATE 108
        slrTable[E108.ordinal()][FUNCOES.ordinal()] = E109.ordinal();
        // [E108][FUNCOES] => [E109]
        slrTable[E108.ordinal()][FUNCAO.ordinal()] = E11.ordinal();
        // [E108][FUNCAO] => [E11]
        slrTable[E108.ordinal()][FUNCTION.ordinal()] = E101.ordinal();
        // [E108][function] => [E101]
        slrTable[E108.ordinal()][T_MAIN.ordinal()] = R40.ordinal();
        // [E108][main] => [R40]
        // STATE 108
        
        // STATE 109
        slrTable[E109.ordinal()][MAIN.ordinal()] = E2.ordinal();
        // [E109][MAIN] => [E2]
        slrTable[E109.ordinal()][T_MAIN.ordinal()] = E20.ordinal();
        // [E109][main] => [E20]
        // STATE 109
        
        // STATE 110
        slrTable[E110.ordinal()][CMDS.ordinal()] = E15.ordinal();
        // [E110][CMDS] => [E15]
        slrTable[E110.ordinal()][CMD.ordinal()] = E24.ordinal();
        // [E110][CMD] => [E24]
        slrTable[E110.ordinal()][IF.ordinal()] = E26.ordinal();
        // [E110][IF] => [E26]
        slrTable[E110.ordinal()][WHILE.ordinal()] = E27.ordinal();
        // [E110][WHILE] => [E27]
        slrTable[E110.ordinal()][FOR.ordinal()] = E28.ordinal();
        // [E110][FOR] => [E28]
        slrTable[E110.ordinal()][ATR.ordinal()] = E29.ordinal();
        // [E110][ATR] => [E29]
        slrTable[E110.ordinal()][CH_FUNC.ordinal()] = E30.ordinal();
        // [E110][CH_FUNC] => [E30]
        slrTable[E110.ordinal()][INCR.ordinal()] = E31.ordinal();
        // [E110][INCR] => [E31]
        slrTable[E110.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E110][id] => [E64]
        slrTable[E110.ordinal()][T_IF.ordinal()] = E33.ordinal();
        // [E110][if] => [E33]
        slrTable[E110.ordinal()][T_WHILE.ordinal()] = E45.ordinal();
        // [E110][while] => [E45]
        slrTable[E110.ordinal()][T_FOR.ordinal()] = E53.ordinal();
        // [E110][for] => [E53]
        // STATE 110
        
        // STATE 111
        slrTable[E111.ordinal()][CMDS.ordinal()] = E22.ordinal();
        // [E111][CMDS] => [E22]
        slrTable[E111.ordinal()][CMD.ordinal()] = E24.ordinal();
        // [E111][CMD] => [E24]
        slrTable[E111.ordinal()][IF.ordinal()] = E26.ordinal();
        // [E111][IF] => [E26]
        slrTable[E111.ordinal()][WHILE.ordinal()] = E27.ordinal();
        // [E111][WHILE] => [E27]
        slrTable[E111.ordinal()][FOR.ordinal()] = E28.ordinal();
        // [E111][FOR] => [E28]
        slrTable[E111.ordinal()][ATR.ordinal()] = E29.ordinal();
        // [E111][ATR] => [E29]
        slrTable[E111.ordinal()][CH_FUNC.ordinal()] = E30.ordinal();
        // [E111][CH_FUNC] => [E30]
        slrTable[E111.ordinal()][INCR.ordinal()] = E31.ordinal();
        // [E111][INCR] => [E31]
        slrTable[E111.ordinal()][ID.ordinal()] = E64.ordinal();
        // [E111][id] => [E64]
        slrTable[E111.ordinal()][T_IF.ordinal()] = E33.ordinal();
        // [E111][if] => [E33]
        slrTable[E111.ordinal()][T_WHILE.ordinal()] = E45.ordinal();
        // [E111][while] => [E45]
        slrTable[E111.ordinal()][T_FOR.ordinal()] = E53.ordinal();
        // [E111][for] => [E53]
        // STATE 111
        
        // END SLR(1) TABLE
        
        return slrTable;
    }
    
    /**
     * Detects and stacks types and ids, rewrite const's types and additionaly
     * trim a token to its lexical
     * @return a substring
     */
    private static String lexicalReader(String lexicItem) {
        StringBuilder sb = new StringBuilder();
        int i = 1; // lexicItem.charAt[0] = '<', ignore that
        
        for (; lexicItem.charAt(i) != LEXICAL_DELIMITER; i++) {
            sb.append(lexicItem.charAt(i));
            // appends char until finding LEXICAL_DELIMITER
        }
        String everything = sb.toString(); // converts back to string
        i++; // walks one step after LEXICAL_DELIMITER
        
        switch (everything) {    
            case LEXICAL_NUM:
                for (; lexicItem.charAt(i) != END_DELIMITER_TOKEN &&
                       lexicItem.charAt(i) != PERIOD_CHAR; i++) {
                }
                
                if (lexicItem.charAt(i) == END_DELIMITER_TOKEN) {
                    // case is int
                    valueTypeStack.push(getIntCode());
                    // stacks int type's code
                }
                else {
                    // case is float
                    valueTypeStack.push(getFloatCode());
                    // stacks float type's code
                }
                
                if (isReadingConst()) { // is this a const value?
                    setReadingConst(false); // not reading const anymore
                    getConstToTypeMap().put(getIdConst(), valueTypeStack.pop());
                    // maps const's id to it's type, pops that value
                }
                
                break;
                
            case LEXICAL_CHAR:
                valueTypeStack.push(getCharCode()); // stacks char type's code
                break;
                
            case LEXICAL_STRING:
                valueTypeStack.push(getStringCode());
                // stacks string type's code
        }
        
        return everything; // returns subtring from lexicItem
    }
    
    /**
     * Checks types on some states.
     */
    private static void typeChecker(int state, String str) {
        
        switch(stateList[state]) {
            case E95: { // pops 2 values
                valueTypeStack.pop();
                valueTypeStack.pop();
                
                break;
            }
            
            case E19: { // pops 1 variable and 1 function of same type
                String variableId = getIdStack().pop(),
                       functionId = getIdStack().pop();
                
                if (whatIsThisId(variableId) != IS_VARIABLE ||
                    whatIsThisId(functionId) != IS_FUNCTION ||
                    !getVariableToTypeMap().get(variableId).
                    equals(getFunctionToTypeMap().get(functionId))) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
                
            case E74: { // pops 1 function and 1 variable of same type
                String functionId = getIdStack().pop(),
                       variableId = getIdStack().pop();
                
                if (whatIsThisId(variableId) != IS_VARIABLE ||
                    whatIsThisId(functionId) != IS_FUNCTION ||
                    !getVariableToTypeMap().get(variableId).
                    equals(getFunctionToTypeMap().get(functionId))) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E76: { // pops 2 variables of same type
                String variableId1 = getIdStack().pop(),
                       variableId2 = getIdStack().pop();
                
                if (whatIsThisId(variableId1) != IS_VARIABLE ||
                    whatIsThisId(variableId2) != IS_VARIABLE ||
                    !getVariableToTypeMap().get(variableId1).
                    equals(getVariableToTypeMap().get(variableId2))) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E67: { // pops 1 variable and 1 value
                        // if variable is int, value can't be float
                String variableId = getIdStack().pop();
                int valueType = valueTypeStack.pop();
                
                if (whatIsThisId(variableId) != IS_VARIABLE ||
                    (getVariableToTypeMap().get(variableId) == getIntCode() &&
                    valueType == getFloatCode())) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E83: { // pops 1 variable and 1 value, both int
                String variableId = getIdStack().pop();
                int valueType = valueTypeStack.pop();
                
                if (whatIsThisId(variableId) != IS_VARIABLE ||
                    getVariableToTypeMap().get(variableId) != getIntCode() ||
                    valueType != getIntCode()) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E71:
            case E73:
            case E96:
            case E99: { // pops 1 variable and 1 value of same type
                String variableId = getIdStack().pop();
                int valueType = valueTypeStack.pop();
                
                if (whatIsThisId(variableId) != IS_VARIABLE ||
                    getVariableToTypeMap().get(variableId) != valueType) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E30: { // pops 1 function int
                String functionId = getIdStack().pop();
                
                if (whatIsThisId(functionId) != IS_FUNCTION ||
                    getFunctionToTypeMap().get(functionId) != getIntCode()) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E80: { // pops 1 variable int
                String variableId = getIdStack().pop();
                
                if (whatIsThisId(variableId) != IS_VARIABLE ||
                    getVariableToTypeMap().get(variableId) != getIntCode()) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E85: { // pops 1 variable and 2 values
                        // if variable is int values can't be float
                String variableId = getIdStack().pop();
                int valueType1 = valueTypeStack.pop(),
                    valueType2 = valueTypeStack.pop();
                
                if (whatIsThisId(variableId) != IS_VARIABLE ||
                    (getVariableToTypeMap().get(variableId) == getIntCode() &&
                    (valueType1 == getFloatCode() ||
                    valueType2 == getFloatCode()))) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E86:
            case E88: { // pops 2 variables and 1 value
                        // if 2º variable is int, 1º variable or value can't be float
                String variableId1 = getIdStack().pop(),
                       variableId2 = getIdStack().pop();
                int valueType = valueTypeStack.pop();
                
                if (whatIsThisId(variableId1) != IS_VARIABLE ||
                    whatIsThisId(variableId2) != IS_VARIABLE ||
                    (getVariableToTypeMap().get(variableId2) == getIntCode() &&
                    (getVariableToTypeMap().get(variableId1) == getFloatCode() ||
                    valueType == getFloatCode()))) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E89: { // pops 3 variables
                        // if 3º variable is int, 1º or 2º variable can't be float
                String variableId1 = getIdStack().pop(),
                       variableId2 = getIdStack().pop(),
                       variableId3 = getIdStack().pop();
                
                if (whatIsThisId(variableId1) != IS_VARIABLE ||
                    whatIsThisId(variableId2) != IS_VARIABLE ||
                    whatIsThisId(variableId3) != IS_VARIABLE ||
                    (getVariableToTypeMap().get(variableId3) == getIntCode() &&
                    (getVariableToTypeMap().get(variableId1) == getFloatCode() ||
                    getVariableToTypeMap().get(variableId2) == getFloatCode()))) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
            
            case E100: { // pops 2 variables int or float
                String variableId1 = getIdStack().pop(),
                       variableId2 = getIdStack().pop();
                
                if (whatIsThisId(variableId1) != IS_VARIABLE ||
                    whatIsThisId(variableId2) != IS_VARIABLE ||
                    (getVariableToTypeMap().get(variableId1) != getIntCode() &&
                    getVariableToTypeMap().get(variableId1) != getFloatCode()) ||
                    (getVariableToTypeMap().get(variableId2) != getIntCode() &&
                    getVariableToTypeMap().get(variableId2) != getFloatCode())) {
                    System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                    System.exit(0); // ends execution
                }
                
                break;
            }
        }
    }
    
}
