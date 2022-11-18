/*
 * File: TokenScanner.java
 * -----------------------
 * This file exports a TokenScanner class that is easy to use in a
 * variety of common applications.
 */

package edu.stanford.cs.java.tokenscanner;

import java.io.IOException;
import java.io.PushbackReader;
import java.io.Reader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.Stack;

/**
 * This class provides a general facility for dividing a character
 * stream into logical units called "tokens", which are strings
 * of consecutive characters that form logical units.
 *
 * <p>To use this class, you must first create an instance of a
 * <code>TokenScanner</code> object using the declaration
 *
 *<pre>
 *    TokenScanner scanner = new TokenScanner(options);
 *</pre>
 *
 * where <code>options</code> is a string that allows the client to
 * control what token types are recognized.
 *
 * <p>The next step is to select a source of input characters for the
 * scanner by calling
 *
 *<pre>
 *    scanner.setInput(<font face="serif;times"><i>source</i></font>);
 *</pre>
 *
 * where <i>source</i> is either a string or a reader.
 *
 * <p>Once you have initialized the scanner, you can retrieve the
 * next token from the token stream by calling
 *
 *<pre>
 *    token = scanner.nextToken();
 *</pre>
 *
 * To determine whether any tokens remain to be read, you can either
 * call the predicate method <code>scanner.hasMoreTokens()</code>
 * or check to see if <code>nextToken</code> returns the empty string.
 *
 * <p>The following code fragment serves as a pattern for processing
 * each token in the string <code>inputString</code>:
 *
 *<pre>
 *    TokenScanner scanner = new TokenScanner.setInput();
 *    while (scanner.hasMoreTokens()) {
 *       String token = scanner.nextToken();
 *       . . . code to process the token . . .
 *    }
 *</pre>
 */

public class TokenScanner {

/**
 * Initializes a new <code>TokenScanner</code> object with a default
 * set of options.  Before reading tokens, you must give the scanner
 * an input stream by calling <code>setInput</code>.
 */

   public TokenScanner() {
      ignoreWhitespaceFlag = false;
      ignoreCommentsFlag = false;
      scanNumbersFlag = false;
      scanStringsFlag = false;
      cpos = 0;
      input = null;
      wordChars = "";
      savedTokens = new Stack<String>();
      operators = new ArrayList<String>();
   }

/**
 * Initializes a new <code>TokenScanner</code> object initialized to
 * read tokens from the specified string.
 *
 * @param str The string from which tokens are read
 */

   public TokenScanner(String str) {
      this();
      setInput(str);
   }

/**
 * Initializes a new <code>TokenScanner</code> object initialized to
 * read tokens from the specified reader.
 *
 * @param rd The reader from which tokens are read
 */

   public TokenScanner(Reader rd) {
      this();
      setInput(rd);
   }

/**
 * Sets this scanner input to the specified string.
 * Any previous input string is discarded.
 *
 * @param str The string from which tokens are read
 */

   public void setInput(String str) {
      setInput(new StringReader(str));
   }

/**
 * Initializes a new scanner object using a reader as input.
 *
 * @param rd The reader from which tokens are read
 */

   public void setInput(Reader rd) {
      savedChars = "";
      savedTokens.clear();
      cpos = 0;
      input = rd;
   }

/**
 * Returns true as long as there are additional tokens for this
 * scanner to read.
 *
 * @return <code>true</code> if the scanner has more tokens
 */

   public boolean hasMoreTokens() {
      String token = nextToken();
      saveToken(token);
      return !token.isEmpty();
   }

/**
 * Returns the next token from this scanner.  If it is called when no
 * tokens are available, <code>nextToken</code> returns the empty string.
 *
 * @return The next token from the scanner
 */

   public String nextToken() {
      if (!savedTokens.isEmpty()) return savedTokens.pop();
      return scanToken();
   }

/**
 * Restores <code>token</code> into this scanner's input stream in such
 * a way that the next time <code>nextToken</code> is called, the scanner
 * will return this token without reading any additional characters
 * from the input.
 *
 * @param token The token being pushed back into the stream
 */

   public void saveToken(String token) {
      savedTokens.push(token);
   }

/**
 * Returns the current position of the scanner in the input stream.
 * If <code>saveToken</code> has been called, this position corresponds
 * to the beginning of the saved token.  If <code>saveToken</code> is
 * called more than once, the return value of <code>getPosition</code>
 * is undefined.
 *
 * @return The position of the scanner in the input stream
 */

   public int getPosition() {
      if (savedTokens.isEmpty()) return cpos;
      return cpos - savedTokens.peek().length();
   }

/**
 * Causes the scanner to ignore whitespace characters.  By default,
 * the scanner treats whitespace characters just like any other
 * non-alphanumeric character and returns them as single-character tokens.
 */

   public void ignoreWhitespace() {
      ignoreWhitespaceFlag = true;
   }

/**
 * Causes the scanner to ignore both <code>/*</code> and <code>//</code>
 * comments appearing in the input.
 */

   public void ignoreComments() {
      ignoreCommentsFlag = true;
   }

/**
 * Causes the scanner to return the longest legal numeric string
 * (integer or real) when it encounters a digit in the input.  By
 * default, numbers are treated just like any alphabetic character.
 */

   public void scanNumbers() {
      scanNumbersFlag = true;
   }

/**
 * Causes the scanner to return strings beginning with either a
 * single or double quote character.  The tokens returned by
 * <code>nextToken</code> include the outer delimiters so that
 * it is possible to tell a string from a word.  By default,
 * the scanner treats these characters just like any operator
 * character.
 *
 * @usage scanner.scanStrings();
 */

   public void scanStrings() {
      scanStringsFlag = true;
   }

/**
 * Adds the characters in <code>str</code> to the set legal in a word.
 * For example, calling <code>addWordCharacters("_")</code> adds the
 * underscore to the set of word characters.
 *
 * @param str A string of characters that can appear in words
 */

   public void addWordCharacters(String str) {
      for (int i = 0; i < str.length(); i++) {
         char ch = str.charAt(i);
         if (wordChars.indexOf(ch) == -1) wordChars += ch;
      }
   }

/**
 * Checks to see if the character <code>ch</code> is valid in a word.
 *
 * @param ch The character to check
 * @return <code>true</code> if the character can be in a word
 */

   public boolean isWordCharacter(int ch) {
      if (ch == -1) return false;
      return Character.isLetterOrDigit(ch)
          || wordChars.indexOf((char) ch) >= 0;
   }

/**
 * Defines a new multicharacter operator.  Whenever you call
 * <code>nextToken</code> when the input stream contains operator
 * characters, the scanner returns the longest possible operator
 * string that can be read at that point.
 *
 * @param op The operator to add
 */

   public void addOperator(String op) {
      operators.add(op);
   }

/**
 * Reads the next token and makes sure it matches the string
 * <code>expected</code>.  If not, <code>verifyToken</code> throws a
 * runtime exception.
 *
 * @param expected The expected token
 */

   public void verifyToken(String expected) {
      String token = nextToken();
      if (token.equals(expected)) return;
      String msg = "Found " + token + " when expecting " + expected;
      throw new RuntimeException(msg);
   }

/**
 * Returns an integer code that identifies the token class.  This
 * code will be equal to one of the following constants:
 *
 *<table>
 *<tr><td><code>&nbsp;&nbsp;EOF&nbsp;&nbsp;</code></td>
 *<td>The end of the input</td></tr>
 *<tr><td><code>&nbsp;&nbsp;SEPARATOR&nbsp;&nbsp;</code></td>
 *<td>A whitespace token</td></tr>
 *<tr><td><code>&nbsp;&nbsp;WORD&nbsp;&nbsp;</code></td>
 *<td>An word</td></tr>
 *<tr><td><code>&nbsp;&nbsp;NUMBER&nbsp;&nbsp;</code></td>
 *<td>A numeric value</td></tr>
 *<tr><td><code>&nbsp;&nbsp;STRING&nbsp;&nbsp;</code></td>
 *<td>A quoted string (<code>"xxx"</code> or <code>'xxx'</code>)</td></tr>
 *<tr><td><code>&nbsp;&nbsp;OPERATOR&nbsp;&nbsp;</code></td>
 *<td>An operator</td></tr>
 *</table>
 *
 * @param token The token being classified
 * @return The type code for that token class
 */

   public int getTokenType(String token) {
      if (token == null || token.length() == 0) return EOF;
      char ch = token.charAt(0);
      if (Character.isWhitespace(ch)) return SEPARATOR;
      if (Character.isDigit(ch)) return NUMBER;
      if ((ch == '"' || ch == '\'')) return STRING;
      if (isWordCharacter(ch)) return WORD;
      return OPERATOR;
   }

/**
 * Reads the next character from the input stream.
 *
 * @return The next character from the input stream
 */

   public int getChar() {
      try {
         cpos++;
         if (!savedChars.isEmpty()) {
            char ch = savedChars.charAt(0);
            savedChars = savedChars.substring(1);
            return ch;
         } else {
            return input.read();
         }
      } catch (IOException ex) {
         throw new RuntimeException(ex.toString());
      }
   }

/**
 * Pushes back the specified character so that it will be read again
 * on the next call to <code>getChar</code>.
 *
 * @param ch The character to push back
 */

   public void ungetChar(int ch) {
      cpos--;
      if (input instanceof PushbackReader) {
         try {
            ((PushbackReader) input).unread(ch);
            return;
         } catch (IOException ex) {
            /* Empty */
         }
      }
      if (ch >= 0) savedChars = (char) ch + savedChars;
   }

/**
 * Returns the string value of a token.  This value is formed by removing
 * any surrounding quotation marks and replacing escape sequences by the
 * appropriate characters.
 */

   public String getStringValue(String token) {
      String str = "";
      int start = 0;
      int finish = token.length();
      if (finish > 1 && (token.charAt(0) == '"' || token.charAt(0) == '\'')) {
         start = 1;
         finish--;
      }
      for (int i = start; i < finish; i++) {
         char ch = token.charAt(i);
         if (ch == '\\') {
            ch = token.charAt(++i);
            if (Character.isDigit(ch) || ch == 'x') {
               int base = 8;
               int maxDigits = 3;
               if (ch == 'x') {
                  base = 16;
                  maxDigits = 2;
                  i++;
               }
               int result = 0;
               int digit = 0;
               int limit = Math.min(finish, i + maxDigits);
               while (i < limit) {
                  ch = token.charAt(i);
                  if (Character.isDigit(ch)) {
                     digit = ch - '0';
                  } else if (base == 16 && ch >= 'A' && ch <= 'F') {
                     digit = ch - 'A' + 10;
                  } else if (base == 16 && ch >= 'a' && ch <= 'f') {
                     digit = ch - 'a' + 10;
                  } else {
                     break;
                  }
                  result = base * result + digit;
                  i++;
               }
               ch = (char) result;
               i--;
            } else {
               switch (ch) {
                case 'a': ch = '\007'; break;
                case 'b': ch = '\b'; break;
                case 'f': ch = '\f'; break;
                case 'n': ch = '\n'; break;
                case 'r': ch = '\r'; break;
                case 't': ch = '\t'; break;
                case 'v': ch = '\013'; break;
                case '"': ch = '"'; break;
                case '\'': ch = '\''; break;
                case '\\': ch = '\\'; break;
               }
            }
         }
         str += ch;
      }
      return str;
   }

/**
 * Scans the next token using a hand-coded finite-state machine.
 */

   private String scanToken() {
      int ch = scanChar();
      if (ch == -1) return "";
      if (scanNumbersFlag && Character.isDigit(ch)) {
         ungetChar(ch);
         return scanNumber();
      }
      if (isWordCharacter(ch)) {
         ungetChar(ch);
         return scanWord();
      }
      if (scanStringsFlag && (ch == '"' || ch == '\'')) {
         ungetChar(ch);
         return scanString();
      }
      String op = "" + (char) ch;
      while (isOperatorPrefix(op)) {
         ch = getChar();
         if (ch == EOF) break;
         op += (char) ch;
      }
      while (op.length() > 1 && !isOperator(op)) {
         ungetChar(op.charAt(op.length() - 1));
         op = op.substring(0, op.length() - 1);
      }
      return op;
   }

/**
 * Scans the next meaningful character from the input, skipping
 * whitespace and comments as appropriate.
 */

   private int scanChar() {
      boolean slashStarComment = false;
      boolean slashSlashComment = false;
      while (true) {
         int ch = getChar();
         if (ignoreWhitespaceFlag && Character.isWhitespace(ch)) {
            if (!isOperator(Character.toString((char) ch))) continue;
         }
         if (slashStarComment) {
            int peek = getChar();
            if (ch == '*' && peek == '/') {
               slashStarComment = false;
            } else {
               ungetChar(peek);
            }
            continue;
         }
         if (slashSlashComment) {
            if (ch == '\n' || ch == '\r') slashSlashComment = false;
            continue;
         }
         if (ignoreCommentsFlag && ch == '/') {
            int peek = getChar();
            if (peek == '*') {
               slashStarComment = true;
               continue;
            } else if (peek == '/') {
               slashSlashComment = true;
               continue;
            } else {
               ungetChar(peek);
            }
         }
         return ch;
      }
   }

/**
 * Scans a word from the input stream.
 */

   private String scanWord() {
      String str = "";
      int ch = getChar();
      while (isWordCharacter(ch)) {
         str += (char) ch;
         ch = getChar();
      }
      ungetChar(ch);
      return str;
   }

/**
 * Scans a number from the input stream.
 */

   private String scanNumber() {
      String str = "";
      int state = INITIAL_STATE;
      int ec = 'E';
      while (state != FINAL_STATE) {
         int ch = getChar();
         switch (state) {
          case INITIAL_STATE:
            if (ch == '0') {
               int peek = getChar();
               if (peek == 'x' || peek == 'X') {
                  str = "0x";
                  continue;
               }
               ungetChar(peek);
            }
            state = BEFORE_DECIMAL_POINT;
            break;
           case BEFORE_DECIMAL_POINT:
            if (ch == '.') {
               state = AFTER_DECIMAL_POINT;
            } else if (ch == 'E' || ch == 'e') {
               state = STARTING_EXPONENT;
            } else if (!Character.isDigit(ch)) {
               state = FINAL_STATE;
            }
            break;
           case AFTER_DECIMAL_POINT:
            if (ch == 'E' || ch == 'e') {
               ec = ch;
               state = STARTING_EXPONENT;
            } else if (!Character.isDigit(ch)) {
               state = FINAL_STATE;
            }
            break;
           case STARTING_EXPONENT:
            if (ch == '+' || ch == '-') {
               state = FOUND_EXPONENT_SIGN;
            } else if (Character.isDigit(ch)) {
               state = SCANNING_EXPONENT;
            } else {
               state = FINAL_STATE;
            }
            break;
           case FOUND_EXPONENT_SIGN:
            if (Character.isDigit(ch)) {
               state = SCANNING_EXPONENT;
            } else {
               ungetChar(ch);
               ch = ec;
               state = FINAL_STATE;
            }
            break;
           case SCANNING_EXPONENT:
            if (!Character.isDigit(ch)) {
               state = FINAL_STATE;
            }
            break;
           }
           if (state == FINAL_STATE) {
              ungetChar(ch);
              break;
           }
           str += (char) ch;
       }
       return str;
   }

/**
 * Scans a string up to a delimiter character.
 */

   private String scanString() {
      char delim = (char) getChar();
      String str = "" + delim;
      int prev = '\0';
      while (true) {
         int ch = getChar();
         if (ch == -1 || (ch == delim && prev != '\\')) break;
         str += (char) ch;
         prev = ch;
      }
      return str + delim;
   }

/**
 * Returns <code>true</code> if <code>op</code> is a defined operator.
 */

   private boolean isOperator(String op) {
      for (int i = 0; i < operators.size(); i++) {
         if (operators.get(i).equals(op)) return true;
      }
      return false;
   }

/**
 * Returns <code>true</code> if <code>op</code> is a prefix of a defined
 * operator.
 */

   private boolean isOperatorPrefix(String op) {
      for (int i = 0; i < operators.size(); i++) {
         if (operators.get(i).startsWith(op)) return true;
      }
      return false;
   }

/* Constants representing the token types */

/** Identifies the EOF token.  */
   public static final int EOF = -1;

/** Identifies a whitespace token. */
   public static final int SEPARATOR = 0;

/** Identifies a word token.  */
   public static final int WORD = 1;

/** Identifies a numeric token. */
   public static final int NUMBER = 2;

/** Identifies a string token. */
   public static final int STRING = 3;

/** Identifies an operator token. */
   public static final int OPERATOR = 4;

/* States in the state machine */

   private static final int INITIAL_STATE = 0;
   private static final int BEFORE_DECIMAL_POINT = 1;
   private static final int AFTER_DECIMAL_POINT = 2;
   private static final int STARTING_EXPONENT = 3;
   private static final int FOUND_EXPONENT_SIGN = 4;
   private static final int SCANNING_EXPONENT = 5;
   private static final int FINAL_STATE = 6;

/* Private instance variables */

   private Reader input;
   private String wordChars;
   private String savedChars;
   private Stack<String> savedTokens;
   private ArrayList<String> operators;
   private int cpos;
   private boolean ignoreWhitespaceFlag;
   private boolean ignoreCommentsFlag;
   private boolean scanNumbersFlag;
   private boolean scanStringsFlag;

}
