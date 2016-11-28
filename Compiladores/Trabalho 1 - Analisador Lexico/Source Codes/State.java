/*
 * Créditos a destacar:
 * http://www.regexplanet.com/advanced/java/index.html
 * http://www.regular-expressions.info/
 */
package lexicanaliser;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.regex.*;
import java.util.List;
import java.util.ArrayList;
import java.util.ListIterator;

/**
 * Defines a abstrate state class, it's variables and methods.
 *
 * @author Henrique Colodetti Escanferla GRR20135427
 */
class State {

    private static PrintWriter writer; // will write "saida.tokens"
    private static String currentState; // initial state
    private static StringBuilder currentToken; // contain, or will, a currentToken
    private static char[] chars; // array of chars to find tokens
    private static int lineNumber = 1; // actual line number for error prints
    private static int index = 0; // to iterate chars
    private static char c; // a char from chars
    private static final char NEW_LINE_CHAR = System.lineSeparator().charAt(0);
    // take platform free new line
    private static List<String> reservedWordsList; // list of reserved words
    private static List<String> typesList; // list of defined types
    private static List<String> idList; // list of reserved words
    private final String type; // type of the state, can be normal, final, error ...
    private final List<Pattern> patternsList; // list of compiled regexes
    private final List<String> statesList; // list of reachable states by this state

    /**
     * Set entry string and another statics all along.
     */
    public static void setStatics(String s)
            throws FileNotFoundException, UnsupportedEncodingException {
        chars = s.toCharArray();
        currentToken = new StringBuilder();
        reservedWordsList = new ArrayList<>();
        typesList = new ArrayList<>();
        idList = new ArrayList<>();
        writer = new PrintWriter("saida.tokens", "UTF-8");
        // open "saida-tokens" to write, will delete before write if it already exist
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
     * @return the type
     */
    public String getType() {
        return type;
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
        System.exit(0); // ends execution of code
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
     * Verifies if it is a reserved word, type or identifier. Populate symbol
     * table of identifiers if needed.
     *
     * @return token name if reserved word, TYPE if type and ID if otherwise
     */
    private static String isReservedWordOrTypeOrId() {
        ListIterator<String> reservedWordsIterator = getReservedWordsList().listIterator();
        ListIterator<String> typesIterator = typesList.listIterator();
        ListIterator<String> idIterator = idList.listIterator();
        boolean notPopulatedID = true; // to verify if it is not a populated identifier

        while (reservedWordsIterator.hasNext()) {
            if (reservedWordsIterator.next().equals(currentToken.toString())) {
                return currentToken.toString();
                // it is a reserved word so return apropriate token name
            }
        }

        while (typesIterator.hasNext()) {
            if (typesIterator.next().equals(currentToken.toString())) {
                return "TYPE";
                // it is a type so return TYPE token name
            }
        }

        while (idIterator.hasNext()) {
            if (idIterator.next().equals(currentToken.toString())) {
                notPopulatedID = false; // it is a populated identifier !
                break; // finish the search
            }
        }

        if (notPopulatedID) { // populate identifier if needed
            idList.add(currentToken.toString());
        }
        return "ID"; // it is a identifier anyway so return ID token name
    }
    
    /**
     * Prints identifier table.
     */
    private void printIdList() {
        ListIterator<String> idIterator = idList.listIterator();
        
        System.out.println("TABELA DE IDENTIFICADORES\n"); // title to print
        while (idIterator.hasNext()) { // print all identifiers
            System.out.println(idIterator.next());
            }
        }
    
    /**
     * States, based on type, command to append char, clean token,
     * print token, print error and exit or ends execution of code.
     * Talks about end of times...
     */
    public void isItTheEnd() throws FileNotFoundException, UnsupportedEncodingException {
        switch (type) {
            case "normal": // normal states that needs to append char to current token
                currentToken.append(c); // include char in currentToken
                break;
            
            case "cleanToken": // cleanToken states that need to clean current token
                currentToken.setLength(0); // clean current token
                break;
            
            case "final": // final token states that dont need the last char
                index--; // last char need to be read again for next token
                writer.println("<" + currentState + ";"
                + currentToken.toString() + ">" + System.lineSeparator());
                // print in "saida.tokens"
                break;

            case "finalReservedWordOrTypeOrID": // final RESERVED/TYPE/ID token state
                index--; // last char need to be read again for next token
                String tokenName = isReservedWordOrTypeOrId();
                // decides if token is reserved word, type or identifier
                switch (tokenName) {
                    case "TYPE": // type token
                        writer.println("<TYPE;" + currentToken.toString() + ">"
                        + System.lineSeparator());
                        // print in "saida.tokens"
                        break;
                    
                    case "ID": // identifier token
                        writer.println("<ID;" + currentToken.toString() + ">"
                        + System.lineSeparator());
                        // print in "saida.tokens"
                        break;
                    
                    default: // reserved word token
                        writer.println("<" + tokenName + ";>"
                        + System.lineSeparator());
                        // print in "saida.tokens"
                        break;
                }
                break;

            case "EOS": // final END OF STRING state
                writer.close(); // close "saida.tokens"
                printIdList(); // prints identifier table
                System.exit(0); // ends execution of code
                break;
            
            case "error": // final error state
                System.out.println("Erro lexico na linha " + lineNumber);
                // print error and line number where it occured
                writer = new PrintWriter("saida.tokens", "UTF-8");
                // delete "saida.tokens" if error
                writer.close(); // close "saida.tokens"
                printIdList(); // prints identifier table
                System.exit(0); // ends execution of code
                break;

            default: // ignoreChar states do nothing here
                break;
        }
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
     * @param type the type to set
     */
    State(String type) {
        this.type = type; // types that state
        patternsList = new ArrayList<>(); // Create list of compiled regexes to match
        statesList = new ArrayList<>(); // Create list of reachable states from that state
    }

}
