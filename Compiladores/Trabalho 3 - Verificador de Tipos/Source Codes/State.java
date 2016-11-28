/*
 * Créditos a destacar:
 * http://www.regexplanet.com/advanced/java/index.html
 * http://www.regular-expressions.info/
 */
package sintaticanaliser;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.regex.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.ListIterator;
import java.util.Map;
import java.util.Stack;
import static sintaticanaliser.LexicAnaliser.LEXICAL_DELIMITER;
import static sintaticanaliser.LexicAnaliser.END_DELIMITER_TOKEN;
import static sintaticanaliser.LexicAnaliser.LEXICAL_CONST;
import static sintaticanaliser.LexicAnaliser.LEXICAL_FUNCTION;
import static sintaticanaliser.LexicAnaliser.LEXICAL_ID;

/**
 * Defines a abstrate state class, it's variables and methods.
 *
 * @author Henrique Colodetti Escanferla GRR20135427
 */
class State {
    
    private static String currentState; //  current State's name
    private static StringBuilder currentToken;
    // contain, or will, the current token
    private static char[] chars; // array of chars to find tokens
    private static char c; // a char from chars
    private static String idConst = null; // current const's id
    private static int lineNumber = 1; // actual line number for error prints
    private static int index = 0; // to iterate chars
    private static int lastType; //  last declared type
    private static boolean readingConst = false; // it's reading const?
    private static boolean readingFunction = false; // it's reading function?
    private static List<String> reservedWordsList; // list of reserved words
    private static List<String> typesList; // list of defined types
    private static final HashMap<String, Integer> variableToTypeMap = new HashMap<>();
    private static final HashMap<String, Integer> functionToTypeMap = new HashMap<>();
    private static final HashMap<String, Integer> constToTypeMap = new HashMap<>();
    // declared consts's stack
    private static final Stack<String> idStack = new Stack<>();
    // declared identifiers's stack
    private static final char NEW_LINE_CHAR = System.lineSeparator().charAt(0);
    // take, platform free, new line
    private static final int  NO_TYPE = -1; // code for inexistent type
    private final List<Pattern> patternsList; // compiled regexes's list
    private final List<String> statesList;
    // list of reachable states by this state
    private final String typeState;
    // typeState of the state, can be normal, final, error ...
    private final String eosToken = "<#" + LEXICAL_DELIMITER +
                                    END_DELIMITER_TOKEN;
                                    // EOS token for sintatic analyser
    public static final int IS_VARIABLE = 0; // code for whatIsThisId case variable
    public static final int IS_FUNCTION = 1; // code for whatIsThisId case function
    public static final int IS_CONST = 2; // code for whatIsThisId case const
    public static final int NOT_FOUND = 3; // code for whatIsThisId case not found
    
    /**
     * Set entry string and another statics all along.
     */
    public static void setStatics(String s)
            throws FileNotFoundException, UnsupportedEncodingException {
        chars = s.toCharArray();
        currentToken = new StringBuilder();
        reservedWordsList = new ArrayList<>();
        typesList = new ArrayList<>();
    }
    
    /**
     * @return the lineNumber
     */
    public static int getLineNumber() {
        return lineNumber;
    }
    
    /**
     * Get the next char to be read in the string chars.
     *
     * @throws IOException
     * @see Automaton.getNextChar
     * @return the next char still not read from the string chars
     */
    private static char getNextChar() throws IOException {
        char ch = chars[index];
        index++; // counting chars
        if (ch == NEW_LINE_CHAR) {
            lineNumber++; // counting lines
        }
        return ch;
    }

    /**
     * @return the typeState
     */
    public String getTypeState() {
        return typeState;
    }

    /**
     * @return the currentToken
     */
    public static StringBuilder getCurrentToken() {
        return currentToken;
    }

    /**
     * @return the currentState
     */
    public static String getCurrentState() {
        return currentState;
    }

    /**
     * @param newCurrentState the currentState to set
     */
    public static void setCurrentState(String newCurrentState) {
        currentState = newCurrentState;
    }

    /**
     * @return the reservedWordsList
     */
    public static List<String> getReservedWordsList() {
        return reservedWordsList;
    }

    /**
     * @return the typesList
     */
    public static List<String> getTypesList() {
        return typesList;
    }

    /**
     * @return the idConst
     */
    public static String getIdConst() {
        return idConst;
    }

    /**
     * @param aIdConst the idConst to set
     */
    public static void setIdConst(String aIdConst) {
        idConst = aIdConst;
    }
    
    /**
     * @return the readingConst
     */
    public static boolean isReadingConst() {
        return readingConst;
    }

    /**
     * @param aWasConst the readingConst to set
     */
    public static void setReadingConst(boolean aWasConst) {
        readingConst = aWasConst;
    }
    
    /**
     * @return the readingFunction
     */
    public static boolean isReadingFunction() {
        return readingFunction;
    }

    /**
     * @param aReadingFunction the readingFunction to set
     */
    public static void setReadingFunction(boolean aReadingFunction) {
        readingFunction = aReadingFunction;
    }
    
    /**
     * @return a unnmodifiable map from variableToTypeMap
     */
    public static Map<String, Integer> getVariableToTypeMap() {
        return Collections.unmodifiableMap(variableToTypeMap);
    }
    
    /**
     * @return a unnmodifiable map from functionToTypeMap
     */
    public static Map<String, Integer> getFunctionToTypeMap() {
        return Collections.unmodifiableMap(functionToTypeMap);
    }
    
    /**
     * @return the constToTypeMap
     */
    public static HashMap<String, Integer> getConstToTypeMap() {
        return constToTypeMap;
    }
    
    /**
     * @return the idStack
     */
    public static Stack<String> getIdStack() {
        return idStack;
    }
    
    /**
     * @param c the char to choose the next state
     * @return the next state
     */
    private String nextState(char c) {
        String seq = "" + c; // sequence to be matched
        ListIterator<Pattern> patternIterator = patternsList.listIterator();
        ListIterator<String> statesIterator = statesList.listIterator();
        while (patternIterator.hasNext() && statesIterator.hasNext()) {
            if (patternIterator.next().matcher(seq).matches()) {
                return statesIterator.next(); // Matched!
            } else {
                statesIterator.next(); // Not matched... go to next pattern
            }
        }
        System.out.println("Nao achou nenhuma transicao valida => ERRO!");
        // transition error
        System.exit(0); // ends execution
        return null;
    }

    /**
     * Add new transition that match regex and goes to state.
     *
     * @param regex the regex to be match
     * @param state the state to go if regex is matched
     */
    public void addTransition(String regex, String state) {
        patternsList.add(Pattern.compile(regex)); // Compile regex and save it
        statesList.add(state); // Add a reachable state
    }
    
    /**
     * Search what declaration is the identifier, if declared.
     * 
     * @param idName the string id
     * @return code for idName's declaration
     */
    public static int whatIsThisId(String idName) {
        if (variableToTypeMap.containsKey(idName)) { // case variable
            return IS_VARIABLE;
        }
        
        if (functionToTypeMap.containsKey(idName)) { // case function
            return IS_FUNCTION;
        }
        
        if (constToTypeMap.containsKey(idName)) { // case const
            return IS_CONST;
        }
        
        return NOT_FOUND; // case not declared yet
    }
      
    /**
     * Populate idName bases upon whatIsThisId output.
     * 
     * @param idName id's string
     */
    private static void populateId(String idName) {
        int code = whatIsThisId(idName); // what type of id is this?
        
        if(code == NOT_FOUND) { // Obs.: all valid types are > NO_TYPE
            if (lastType == NO_TYPE && !isReadingConst()) {
                // case this isn't a declaration
                System.out.println("\nErro de tipo na linha " +
                                       getLineNumber()); // type error
                System.exit(0); // ends execution
            }
            else {
                if (isReadingConst()) { // case it's a const
                    // can't setReadingConst(false) here
                    // will maps const's id to it's type after
                    setIdConst(idName); // sets current const's id
                    // see SintaticAnaliser.lexicReader switch case LEXIC_NUM
                }
                else {
                    if (isReadingFunction()) { // case it's a function
                        setReadingFunction(false); // not reading function anymore
                        functionToTypeMap.put(idName, lastType);
                        // maps function id to it's type
                        idStack.push(idName);
                        // need to remember function's name to verify later
                    }
                    else { // case it's a variable
                        variableToTypeMap.put(idName, lastType);
                        // maps variable id to it's type
                    }
                    
                    lastType = NO_TYPE; // "erases" previous type
                }
            }
        }
        else { // Obs.: all valid types are > NO_TYPE
            if (lastType > NO_TYPE || isReadingConst()) {
                // case this is a declaration
                System.out.println("\nErro de tipo na linha " +
                                   getLineNumber()); // type error
                System.exit(0); // ends execution
            }
                
            getIdStack().push(idName); // stacks id's name and verify after
            // see SintaticAnaliser.typeChecker
        }
    }
    
    /**
     * Verifies if it is a reserved word, typeState or identifier. Populate symbol
     * table of identifiers if needed. Do some cases of type verification.
     *
     * @return token name if reserved word, typeState if typeState and id if otherwise
     */
    private static String isReservedWordOrTypeOrId() {
        ListIterator<String> reservedWordsIterator = getReservedWordsList().listIterator();
        ListIterator<String> typesIterator = typesList.listIterator();

        while (reservedWordsIterator.hasNext()) {
            if (reservedWordsIterator.next().equals(currentToken.toString())) {
                if (currentToken.toString().equals(LEXICAL_CONST)) {
                    setReadingConst(true); // reading const
                }
                
                if (currentToken.toString().equals(LEXICAL_FUNCTION)) {
                    setReadingFunction(true); // reading function
                }
                
                return currentToken.toString();
                // it is a reserved word so return apropriate token name
            }
        }

        while (typesIterator.hasNext()) {
            if (typesIterator.next().equals(currentToken.toString())) {
                lastType = typesIterator.nextIndex() - 1;
                // save current index as a code to map with declared id
                return "type";
                // it is a type so return type's lexical
            }
        }
        
        populateId(currentToken.toString()); // populate that identifier
        
        return LEXICAL_ID; // it is a identifier anyway so return id's lexical
    }
    
    /**
     * Prints identifier table.
     */
    private void printIdList() {
        
        System.out.println("\nTABELA DE SIMBOLOS\n"); // title to print
        for (String key : getVariableToTypeMap().keySet()) { // print all identifiers
            System.out.println(key);
            }
        System.out.println("\nFIM DA TABELA DE SIMBOLOS"); // jump a line TEST
        
        }
    
    /**
     * States, based on typeState, command to append char, clean token,
 print token, print error and exit or ends execution of code.
     * Talks about end of times...
     */
    public String isItTheEnd() throws FileNotFoundException, UnsupportedEncodingException {
        switch (typeState) {
            case "normal": // normal states that needs to append char to current token
                currentToken.append(c); // include char in currentToken
                break;
            
            case "cleanToken": // cleanToken states that need to clean current token
                currentToken.setLength(0); // clean current token and ignore char
                break;
            
            case "final": // final token states that dont need the last char
                if (chars[index - 1] != NEW_LINE_CHAR) {
                    index--; // last char need to be read again for next token
                }
                return "<" + currentState + ";" + currentToken.toString() + ">";

            case "finalReservedWordOrTypeOrID":
            // final RESERVED/type/id token state
                if (chars[index - 1] != NEW_LINE_CHAR) { // if not '\n'
                    index--; // last char need to be read again for next token
                }
                String tokenName = isReservedWordOrTypeOrId();
                // decides if token is reserved word, typeState or identifier
                switch (tokenName) {
                    case "type": // typeState token
                        return "<type;" + currentToken.toString() +
                               END_DELIMITER_TOKEN;
                    
                    case LEXICAL_ID: // identifier token
                        return "<" + LEXICAL_ID + ";" + currentToken.toString() +
                               END_DELIMITER_TOKEN;
                    
                    default: // reserved word token
                        return"<" + tokenName + ";" + END_DELIMITER_TOKEN;
                }

            case "finalEOS": // final END OF STRING state
                printIdList(); // prints identifier table
                return eosToken; // EOS's token for sintatic analyser
            
            case "error": // final error state
                System.out.println("\nErro lexico na linha " + getLineNumber());
                // print error and line number where it occured
                printIdList(); // prints identifier table
                System.exit(0); // ends execution
                break;

        //  default: ignoreChar states do nothing here
        }
        return "ERROR";
    }

    /**
     * @param regex the regex to be match
     * @param state the state to go if regex is matched
     */
    public void execute() throws IOException {
        c = getNextChar(); // read current char from "entry.code"
        setCurrentState(nextState(c)); // make transition
    }

    /**
     * @param type the typeState to set
     */
    State(String type) {
        this.typeState = type; // types that state
        patternsList = new ArrayList<>(); // Create list of compiled regexes to match
        statesList = new ArrayList<>(); // Create list of reachable states from that state
    }

}
