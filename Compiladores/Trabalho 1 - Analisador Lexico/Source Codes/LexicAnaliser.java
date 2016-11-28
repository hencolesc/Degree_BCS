/*
 * Créditos a destacar:
 * http://www.regexplanet.com/advanced/java/index.html
 * http://www.regular-expressions.info/
 */
package lexicanaliser;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author Henrique Colodetti Escanferla GRR20135427
 */
public class LexicAnaliser {

    /** Defines the full process of analising a code and converting to tokens.
     * 
     * @param args the arguments for main method
     * @see Automaton
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        State.setStatics(read()); // transforms "entry.code" into an array of chars to be read
        Automaton.build();
        // builds states, respective transitions (regex, state)
        // and fill tables of reserved words/types
        for(;true;) { // keeps recognizing until lexic error or EOS
            Automaton.execute(); // recognize a token from array of chars
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
    
}
