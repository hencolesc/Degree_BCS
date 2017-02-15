/*
 * Fonte de informações sobre expressões regulares utilizada:
 * http://www.regexplanet.com/advanced/java/index.html
 * http://www.regular-expressions.info/
 */
package sintaticanaliser;

import java.io.IOException;
import java.util.HashMap;

/** Defines a deterministic finit automaton to implement a lexic
 *  analiser.
 *
 * @author Henrique Colodetti Escanferla GRR20135427
 */
abstract class LexicAnaliser {
    private static final HashMap<String, State> nameToStateMap = new HashMap<>();

/**
* Build, name and type all states putting respectives
* regexes to transit in the automaton.
*/   
    public static void build() {
        String digit = "0-9"; // any digit
        String letter = "a-zA-Z"; // any letter
        String idChar = "0-9a-zA-Z"; // any digit or letter
        String anything = "\\s\\S"; // any character
        String nullChar = "\\x00"; // null character
        String whitespacesOrBreakLine = "\\s\\t" + System.lineSeparator();
        // whitespace chars or break line
        String ab = idChar + "+\\-*/&|\\\\=><!,;(){}\"'.\\s-"
        + System.lineSeparator() + nullChar;
        // whole alphabet of accepted characters in automaton
        
        // START OF RESERVED WORDS
        State.getReservedWordsList().add("if"); // command if
        State.getReservedWordsList().add("then"); // command then
        State.getReservedWordsList().add("else"); // command else
        State.getReservedWordsList().add("while"); // command while
        State.getReservedWordsList().add("do"); // command do
        State.getReservedWordsList().add("for"); // command for
        State.getReservedWordsList().add("return"); // command return
        State.getReservedWordsList().add("const"); // command const
        State.getReservedWordsList().add("function"); // command function
        State.getReservedWordsList().add("main"); // command main
        // END OF RESERVED WORDS
        
        // START OF DEFINED TYPES
        State.getTypesList().add("int"); // type integer
        State.getTypesList().add("float"); // type float
        State.getTypesList().add("string"); // type string
        State.getTypesList().add("char"); // type char
        // END OF DEFINED TYPES
        
        // START OF ESSENCIAL STATES
        nameToStateMap.put("s0", new State("ignoreChar"));
        // ignoreChar initial state "s0"
        nameToStateMap.put("eos0", new State("finalEOS")); // final state "finalEOS"
        nameToStateMap.put("er0", new State("error")); // final error state "er0"
        // END OF ESSENCIAL STATES
        
        // START OF "S0" TRANSITIONS
        nameToStateMap.get("s0").addTransition("[" + digit + "]", "num0");
        // read digit => "s0" to "num0"
        nameToStateMap.get("s0").addTransition("[" + letter + "]", "id0");
        // read letter => "s0" to "id0"
        nameToStateMap.get("s0").addTransition("[\"]", "str0");
        // read double quote => "s0" to "str0"
        nameToStateMap.get("s0").addTransition("[']", "ch0");
        // read simple quote => "s0" to "ch0"
        nameToStateMap.get("s0").addTransition("[+]", "+0");
        // read + => "s0" to "+0"
        nameToStateMap.get("s0").addTransition("[-]", "-0");
        // read - => "s0" to "-0"
        nameToStateMap.get("s0").addTransition("[*]", "*0");
        // read * => "s0" to "*0"
        nameToStateMap.get("s0").addTransition("[/]", "/Orcomment0");
        // read / => "s0" to "/Orcomment0"
        nameToStateMap.get("s0").addTransition("[><]", "rel0");
        // read > or < => "s0" to "rel0"
        nameToStateMap.get("s0").addTransition("[=]", "=0");
        // read = => "s0" to "=0"
        nameToStateMap.get("s0").addTransition("[!]", "!0");
        // read ! => "s0" to "!0"
        nameToStateMap.get("s0").addTransition("[&]", "log0");
        // read & => "s0" to "log0"
        nameToStateMap.get("s0").addTransition("[|]", "log1");
        // read | => "s0" to "log1"
        nameToStateMap.get("s0").addTransition("[;]", "semiColon0");
        // read ; => "s0" to "semiColon0"
        nameToStateMap.get("s0").addTransition("[(]", "leftParent0");
        // read ( => "s0" to "leftParent0"
        nameToStateMap.get("s0").addTransition("[)]", "rightParent0");
        // read ) => "s0" to "rightParent0"
        nameToStateMap.get("s0").addTransition("[{]", "leftBrace0");
        // read { => "s0" to "leftBrace0"
        nameToStateMap.get("s0").addTransition("[}]", "rightBrace0");
        // read } => "s0" to "rightBrace0"
        nameToStateMap.get("s0").addTransition("[" + nullChar + "]", "eos0");
        // read EOS => "s0" to "eos0"
        nameToStateMap.get("s0").addTransition("[" + whitespacesOrBreakLine + "]", "s0");
        // read whitespace or break line char => "s0" to "s0"
        nameToStateMap.get("s0").addTransition("[" + anything + "]", "er0");
        // read anything else => "s0" to "er0"
        // END OF "S0" TRANSITIONS
        
        // START OF num TOKEN STATES
        nameToStateMap.put("num0", new State("normal")); // normal number state "num0"
        nameToStateMap.put("num1", new State("normal")); // normal number state "num1"
        nameToStateMap.put("num2", new State("normal")); // normal number state "num2"
        nameToStateMap.put("num", new State("final")); // final number token state "num"
        
        // END OF num TOKEN STATES
        
        // START OF "num0" TRANSITIONS
        nameToStateMap.get("num0").addTransition("[" + digit + "]", "num0");
        // read digit => "num0" to "num0"
        nameToStateMap.get("num0").addTransition("[.]", "num1");
        // read period => "num0" to "num1"
        nameToStateMap.get("num0").addTransition("[" + ab + "]", "num");
        // read ab char => "num0" to "num"
        nameToStateMap.get("num0").addTransition("[" + anything + "]", "er0");
        // read no digit no period and no ab char => "num0" to "er0"
        // END OF "num0" TRANSITIONS
        
        // START OF "num1" TRANSITIONS
        nameToStateMap.get("num1").addTransition("[" + digit + "]", "num2");
        // read digit => "num1" to "num2"
        nameToStateMap.get("num1").addTransition("[" + anything + "]", "er0");
        // read no digit => "num1" to "er0"
        // END OF "num1" TRANSITIONS
        
        // START OF "num2" TRANSITIONS
        nameToStateMap.get("num2").addTransition("[" + digit + "]", "num2");
        // read digit => "num2" to "num2"
        nameToStateMap.get("num2").addTransition("[.]", "er0");
        // read period => "num2" to "er0"
        nameToStateMap.get("num2").addTransition("[" + ab + "]", "num");
        // read ab char => "num2" to "num"
        nameToStateMap.get("num2").addTransition("[" + anything + "]", "er0");
        // read no digit no period and no ab char => "num2" to "er0"
        // END OF "num2" TRANSITIONS
        
        // START OF RESERVED WORD/TYPE/ID TOKEN STATES
        nameToStateMap.put("id0", new State("normal"));
        // normal reserved word/type/id state "id0"
        nameToStateMap.put("RESERVED WORD/TYPE/ID",
        new State("finalReservedWordOrTypeOrID"));
        // final RESERVED WORD/TYPE/ID token state "RESERVED WORD/TYPE/ID"
        // END OF RESERVED WORD/TYPE/ID TOKEN STATES
        
        // START OF "id0" TRANSITIONS
        nameToStateMap.get("id0").addTransition("[" + idChar + "]", "id0");
        // read id valid char => "id0" to "id0"
        nameToStateMap.get("id0").addTransition("[" + ab + "]", "RESERVED WORD/TYPE/ID");
        // read ab no id valid char => "id0" to "RESERVED WORD/TYPE/ID"
        nameToStateMap.get("id0").addTransition("[" + anything + "]", "er0");
        // read no ab => "id0" to "er0"
        // END OF "id0" TRANSITIONS
        
        // START OF str TOKEN STATES
        nameToStateMap.put("str0", new State("ignoreChar"));
        // ignoreChar string state "str0"
        nameToStateMap.put("str1", new State("normal")); // normal string state "str1"
        nameToStateMap.put("str2", new State("ignoreChar")); // ignore string state "str2"
        nameToStateMap.put("str", new State("final"));
        // final string token state "str"
        // END OF str TOKEN STATES
        
        // START OF "str0" TRANSITIONS
        nameToStateMap.get("str0").addTransition("[" + nullChar + "]", "er0");
        // read EOS => "str0" to "er0"
        nameToStateMap.get("str0").addTransition("[\"]", "str2");
        // read double quote => "str0" to "str2"
        nameToStateMap.get("str0").addTransition("[^\"]", "str1");
        // read no double quote => "str0" to "str1"
        // END OF "str0" TRANSITIONS
        
        // START OF "str1" TRANSITIONS
        nameToStateMap.get("str1").addTransition("[" + nullChar + "]", "er0");
        // read EOS => "str1" to "er0"
        nameToStateMap.get("str1").addTransition("[\"]", "str2");
        // read double quote => "str1" to "str2"
        nameToStateMap.get("str1").addTransition("[^\"]", "str1");
        // read no double quote => "str1" to "str1"
        // END OF "str1" TRANSITIONS
        
        // START OF "str2" TRANSITIONS
        nameToStateMap.get("str2").addTransition("[" + ab + "]", "str");
        // read ab => "str2" to "str"
        nameToStateMap.get("str2").addTransition("[" + anything + "]", "er0");
        // read no ab => "str2" to "er0"
        // END OF "str2" TRANSITIONS
        
        // START OF ch TOKEN STATES
        nameToStateMap.put("ch0", new State("ignoreChar"));
        // ignoreChar char state "ch0"
        nameToStateMap.put("ch1", new State("normal")); // normal char state "ch1"
        nameToStateMap.put("ch2", new State("ignoreChar")); // ignore string state "ch2"
        nameToStateMap.put("ch", new State("final"));
        // final char token state "ch"
        // END OF ch TOKEN STATES
        
        // START OF "ch0" TRANSITIONS
        nameToStateMap.get("ch0").addTransition("[" + nullChar + "]", "er0");
        // read EOS => "ch0" to "er0"
        nameToStateMap.get("ch0").addTransition("[']", "ch2");
        // read simple quote => "ch0" to "ch2"
        nameToStateMap.get("ch0").addTransition("[^']", "ch1");
        // read no simple quote => "ch0" to "ch1"
        // END OF "ch0" TRANSITIONS
        
        // START OF "ch1" TRANSITIONS
        nameToStateMap.get("ch1").addTransition("[']", "ch2");
        // read simple quote => "ch1" to "ch2"
        nameToStateMap.get("ch1").addTransition("[" + anything + "]", "er0");
        // read no simple quote => "ch1" to "er0"
        // END OF "ch1" TRANSITIONS
        
        // START OF "ch2" TRANSITIONS
        nameToStateMap.get("ch2").addTransition("[" + ab + "]", "ch");
        // read ab => "ch2" to "ch"
        nameToStateMap.get("ch2").addTransition("[" + anything + "]", "er0");
        // read no ab => "ch2" to "er0"
        // END OF "ch2" TRANSITIONS
        
        // START OF op_art/inc TOKEN STATES
        nameToStateMap.put("+0", new State("normal")); // normal op_art/inc state "+0"
        nameToStateMap.put("-0", new State("normal")); // normal op_art/inc state "-0"
        nameToStateMap.put("*0", new State("normal")); // normal op_art state "*0"
        nameToStateMap.put("/Orcomment0", new State("normal"));
        // normal op_art/comment state "/Orcomment0"
        nameToStateMap.put("inc0", new State("normal")); // normal inc state "inc0"
        nameToStateMap.put("op_art", new State("final"));
        // final op_art token state "op_art"
        nameToStateMap.put("inc", new State("final"));
        // finalTakeChar inc token state "inc"
        // END OF op_art/inc TOKEN STATES
        
        // START OF "+0" TRANSITIONS
        nameToStateMap.get("+0").addTransition("[+]", "inc0"); // read + => "+0" to "inc0"
        nameToStateMap.get("+0").addTransition("[" + ab + "]", "op_art");
        // read ab no + => "+0" to "op_art"
        nameToStateMap.get("+0").addTransition("[" + anything + "]", "er0");
        // read no ab => "+0" to "er0"
        // END OF "+0" TRANSITIONS
        
        // START OF "-0" TRANSITIONS
        nameToStateMap.get("-0").addTransition("[-]", "inc0"); // read - => "-0" to "inc0"
        nameToStateMap.get("-0").addTransition("[" + ab + "]", "op_art");
        // read ab no - => "-0" to "op_art"
        nameToStateMap.get("-0").addTransition("[" + anything + "]", "er0");
        // read no ab => "-0" to "er0"
        // END OF "-0" TRANSITIONS
        
        // START OF "*0" TRANSITIONS
        nameToStateMap.get("*0").addTransition("[" + ab + "]", "op_art");
        // read ab => "*0" to "op_art"
        nameToStateMap.get("*0").addTransition("[" + anything + "]", "er0");
        // read no ab => "*0" to "er0"
        // END OF "*0" TRANSITIONS
        
        // START OF "/Orcomment0" TRANSITIONS
        nameToStateMap.get("/Orcomment0").addTransition("[/]", "comment1");
        // read / => "/Orcomment0" to "comment1"
        nameToStateMap.get("/Orcomment0").addTransition("[*]", "comment2");
        // read * => "/Orcomment0" to "comment2"
        nameToStateMap.get("/Orcomment0").addTransition("[" + ab + "]", "op_art");
        // read ab no * no / => "/Orcomment0" to "op_art"
        nameToStateMap.get("/Orcomment0").addTransition("[" + anything + "]", "er0");
        // read no ab => "/Orcomment0" to "er0"
        // END OF "/Orcomment0" TRANSITIONS
        
        // START OF "inc0" TRANSITIONS
        nameToStateMap.get("inc0").addTransition("[" + ab + "]", "inc");
        // read ab => "inc0" to "inc"
        nameToStateMap.get("inc0").addTransition("[" + anything + "]", "er0");
        // read no ab => "inc0" to "er0"
        // END OF "inc0" TRANSITIONS
        
        // START OF op_rel/=/op_log TOKEN STATES
        nameToStateMap.put("rel0", new State("normal")); // normal op_rel state "rel0"
        nameToStateMap.put("rel1", new State("normal")); // normal op_rel state "rel1"
        nameToStateMap.put("=0", new State("normal"));
        // normal art/op_logic state "=0"
        nameToStateMap.put("!0", new State("normal"));
        // normal op_rel/op_log state "!0"
        nameToStateMap.put("log0", new State("normal"));
        // normal op_log state "log0"
        nameToStateMap.put("log1", new State("normal"));
        // normal op_log state "log1"
        nameToStateMap.put("log2", new State("normal"));
        // normal op_log state "log2"
        nameToStateMap.put("op_rel", new State("final"));
        // final op_rel token state "op_rel"
        nameToStateMap.put("=", new State("final"));
        // final = token state "="
        nameToStateMap.put("op_log", new State("final"));
        // final op_log token state "op_log"
        // END OF op_rel/=/op_logIC TOKEN STATES
        
        // START OF "rel0" TRANSITIONS
        nameToStateMap.get("rel0").addTransition("[=]", "rel1");
        // read = => "rel0" to "rel1"
        nameToStateMap.get("rel0").addTransition("[" + ab + "]", "op_rel");
        // read ab no = => "rel0" to "op_rel"
        nameToStateMap.get("rel0").addTransition("[" + anything + "]", "er0");
        // read no ab => "rel0" to "er0"
        // END OF "rel0" TRANSITIONS
        
        // START OF "rel1" TRANSITIONS
        nameToStateMap.get("rel1").addTransition("[" + ab + "]", "op_rel");
        // read ab => "rel1" to "op_rel"
        nameToStateMap.get("rel1").addTransition("[" + anything + "]", "er0");
        // read no ab => "rel1" to "er0"
        // END OF "rel1" TRANSITIONS
        
        // START OF "=0" TRANSITIONS
        nameToStateMap.get("=0").addTransition("[=]", "rel1");
        // read = => "=0" to "rel1"
        nameToStateMap.get("=0").addTransition("[" + ab + "]", "=");
        // read ab no = => "=0" to "="
        nameToStateMap.get("=0").addTransition("[" + anything + "]", "er0");
        // read no ab => "=0" to "er0"
        // END OF "=0" TRANSITIONS
        
        // START OF "!0" TRANSITIONS
        nameToStateMap.get("!0").addTransition("[=]", "rel1");
        // read = => "!0" to "rel1"
        nameToStateMap.get("!0").addTransition("[" + ab + "]", "op_log");
        // read ab no = => "!0" to "op_log"
        nameToStateMap.get("!0").addTransition("[" + anything + "]", "er0");
        // read no ab => "!0" to "er0"
        // END OF "!0" TRANSITIONS
        
        // START OF "log0" TRANSITIONS
        nameToStateMap.get("log0").addTransition("[&]", "log2");
        // read & => "log0" to "log2"
        nameToStateMap.get("log0").addTransition("[" + anything + "]", "er0");
        // read no & => "log0" to "er0"
        // END OF "log0" TRANSITIONS
        
        // START OF "log1" TRANSITIONS
        nameToStateMap.get("log1").addTransition("[|]", "log2");
        // read | => "log1" to "log2"
        nameToStateMap.get("log1").addTransition("[" + anything + "]", "er0");
        // read no | => "log1" to "er0"
        // END OF "log1" TRANSITIONS
        
        // START OF "log2" TRANSITIONS
        nameToStateMap.get("log2").addTransition("[" + ab + "]", "op_log");
        // read ab => "log2" to "op_log"
        nameToStateMap.get("log2").addTransition("[" + anything + "]", "er0");
        // read no ab => "log2" to "er0"
        // END OF "log2" TRANSITIONS
        
        // START OF GENERAL DELIMITERS TOKEN STATES
        nameToStateMap.put("semiColon0", new State("normal"));
        // normal semi_colon state "semiColon0"
        nameToStateMap.put("leftParent0", new State("normal"));
        // normal lparent state "leftParent0"
        nameToStateMap.put("rightParent0", new State("normal"));
        // normal rparent state "rightParent0"
        nameToStateMap.put("leftBrace0", new State("normal"));
        // normal lbrace state "leftBrace0"
        nameToStateMap.put("rightBrace0", new State("normal"));
        // normal rbrace state "rightBrace0"
        nameToStateMap.put("sm", new State("final"));
        // final semi_colon token state "sm"
        nameToStateMap.put("(", new State("final"));
        // final lparent token state "("
        nameToStateMap.put(")", new State("final"));
        // final rparent token state ")"
        nameToStateMap.put("{", new State("final"));
        // final lbrace token state "{"
        nameToStateMap.put("}", new State("final"));
        // final rbrace token state "}"
        // END OF GENERAL DELIMITERS TOKEN STATES
        
        // START OF "semiColon0" TRANSITIONS
        nameToStateMap.get("semiColon0").addTransition("[" + ab + "]", "sm");
        // read ab => "semiColon0" to "sm"
        nameToStateMap.get("semiColon0").addTransition("[" + anything + "]", "er0");
        // read no ab => "semiColon0" to "er0"
        // END OF "semiColon0" TRANSITIONS
                
        // START OF "leftParent0" TRANSITIONS
        nameToStateMap.get("leftParent0").addTransition("[" + ab + "]", "(");
        // read ab => "leftParent0" to "("
        nameToStateMap.get("leftParent0").addTransition("[" + anything + "]", "er0");
        // read no ab => "leftParent0" to "er0"
        // END OF "leftParent0" TRANSITIONS
        
        // START OF "rightParent0" TRANSITIONS
        nameToStateMap.get("rightParent0").addTransition("[" + ab + "]", ")");
        // read ab => "rightParent0" to ")"
        nameToStateMap.get("rightParent0").addTransition("[" + anything + "]", "er0");
        // read no ab => "rightParent0" to "er0"
        // END OF "rightParent0" TRANSITIONS
        
        // START OF "leftBrace0" TRANSITIONS
        nameToStateMap.get("leftBrace0").addTransition("[" + ab + "]", "{");
        // read ab => "leftBrace0" to "{"
        nameToStateMap.get("leftBrace0").addTransition("[" + anything + "]", "er0");
        // read no ab => "leftBrace0" to "er0"
        // END OF "leftBrace0" TRANSITIONS
        
        // START OF "rightBrace0" TRANSITIONS
        nameToStateMap.get("rightBrace0").addTransition("[" + ab + "]", "}");
        // read ab => "rightBrace0" to "}"
        nameToStateMap.get("rightBrace0").addTransition("[" + anything + "]", "er0");
        // read no ab => "rightBrace0" to "er0"
        // END OF "rightBrace0" TRANSITIONS
        
        // START OF COMMENT STATES
        //nameToStateMap.put("/Orcomment0", new State("normal"));
        // normal op_art/comment state "/Orcomment0" already defined in op_art/inc
        nameToStateMap.put("comment1", new State("cleanToken"));
        // cleanToken comment state "comment1"
        nameToStateMap.put("comment2", new State("cleanToken"));
        // cleanToken comment state "comment2"
        nameToStateMap.put("comment3", new State("ignoreChar"));
        // ignoreChar comment state "comment3"
        // END OF COMMENT STATES
        
        // START OF "/Orcomment0" TRANSITIONS ALREADY DEFINED IN op_art/inc TOKEN STATES
        // nameToStateMap.get("/Orcomment0").addTransition("[/]", "comment1");
        // read / => "/Orcomment0" to "comment1"
        // nameToStateMap.get("/Orcomment0").addTransition("[*]", "comment2");
        // read * => "/Orcomment0" to "comment2"
        // nameToStateMap.get("/Orcomment0").addTransition("[" + ab + "]", "op_art");
        // read ab no * no / => "/Orcomment0" to "op_art"
        // nameToStateMap.get("/Orcomment0").addTransition("[" + anything + "]", "er0");
        // read no ab => "/Orcomment0" to "er0"
        // END OF "/Orcomment0" TRANSITIONS ALREADY DEFINED IN op_art/inc TOKEN STATES
        
        // START OF "comment1" TRANSITIONS
        nameToStateMap.get("comment1").
        addTransition("[" + System.lineSeparator() + "]", "s0");
        // read \n => "comment1" to "s0"
        nameToStateMap.get("comment1").addTransition("[" + nullChar + "]", "eos0");
        // read EOS => "comment1" to "eos0"
        nameToStateMap.get("comment1").addTransition("[" + anything + "]", "comment1");
        // read no \n no EOS => "comment1" to "comment1"
        // END OF "comment1" TRANSITIONS
        
        // START OF "comment2" TRANSITIONS
        nameToStateMap.get("comment2").addTransition("[*]", "comment3");
        // read * => "comment2" to "comment3"
        nameToStateMap.get("comment2").addTransition("[" + nullChar + "]", "er0");
        // read EOS => "comment2" to "er0"
        nameToStateMap.get("comment2").addTransition("[" + anything + "]", "comment2");
        // read no * no EOS => "comment2" to "comment2"
        // END OF "comment2" TRANSITIONS
        
        // START OF "comment3" TRANSITIONS
        nameToStateMap.get("comment3").addTransition("[/]", "s0");
        // read / => "comment3" to "s0"
        nameToStateMap.get("comment3").addTransition("[" + nullChar + "]", "er0");
        // read EOS => "comment3" to "er0"
        nameToStateMap.get("comment3").addTransition("[" + anything + "]", "comment2");
        // read no / no EOS => "comment3" to "comment2"
        // END OF "comment3" TRANSITIONS
    }

/**
* Execute the recognition of a token from chars.
*/
    public static String execute() throws IOException { // TODO tests
        State.setCurrentState("s0"); // initial state is "s0"
        State.getCurrentToken().setLength(0); // clear string
        String str = "ERROR";

        // if last executed stated is typed starting with "final" then a token was found
        while(!(nameToStateMap.get(State.getCurrentState()).getType().startsWith("final"))) {
            nameToStateMap.get(State.getCurrentState()).execute();
            // read char and find nextState
            str = nameToStateMap.get(State.getCurrentState()).isItTheEnd();
            // if currentState is a final state, print token, error or ends execution
            // otherwise append char to current token
        }
        return str;

    }

    private LexicAnaliser() {
        
    }

}
