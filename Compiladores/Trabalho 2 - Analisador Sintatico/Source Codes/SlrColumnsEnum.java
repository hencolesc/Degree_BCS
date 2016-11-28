/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sintaticanaliser;

/** Enumeration of columns consts of SlrTable
 * @see SlrTable
 * @author Henrique Colodetti Escanferla GRR20135427
 */
public enum SlrColumnsEnum {
    PROG("PROG"), DECL_VAR("DECL_VAR"), CONST("CONST"),
    FUNCOES("FUNCOES"), FUNCAO("FUNCAO"), MAIN("MAIN"), CMDS("CMDS"),
    CMD("CMD"), IF("IF"), WHILE("WHILE"), FOR("FOR"), ATR("ATR"),
    CH_FUNC("CH_FUNC"), INCR("INCR"), ATR_FOR("ATR_FOR"),
    EXPR_MAT("EXPR_MAT"), TESTE("TESTE"), EXPR_REL("EXPR_REL"),
    STR("str"), CH("ch"), NUM("num"), ID("id"), TYPE("type"),
    T_IF("if"), T_CONST("const"), THEN("then"), ELSE("else"),
    T_WHILE("while"), DO("do"), T_FOR("for"), OP_ART("op_art"),
    OP_REL("op_rel"), INC("inc"), OP_LOG("op_log"),
    RETURN("return"), FUNCTION("function"), T_MAIN("main"),
    SEMI_COLON("sm"), L_PARENT("("), R_PARENT(")"), L_BRACE("{"),
    R_BRACE("}"), EQUAL("="), HASHTAG("#");

    // uses ordinal as identifier for everyone
    private final String lexic; // need strings mapped to column index
    
    /** Creation of SlrColumnsEnum elements
     *
     * @author Henrique Colodetti Escanferla GRR20135427
     */
    private SlrColumnsEnum(String lexic) {
        this.lexic = lexic; // sets lexic
    }
        
    /** Find the enum const by a lexic and return num
     *
     * @param s
     * @return num of enum's item
     */
    public static int findByLexic(String s){
    for(SlrColumnsEnum item : values()){
        if( item.getLexic().equals(s)){
            return item.ordinal();
        }
    }
    System.out.println("Nao achei item de enum para string dada! FIM DE EXECUCAO!");
    // msg if error inside this function, ends execution in next line
    System.exit(0);
    return -1;
}

    /**
     * @return the lexic
     */
    public String getLexic() {
        return lexic;
    }
    
}
