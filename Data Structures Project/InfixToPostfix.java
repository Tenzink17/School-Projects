package InfixToPostfix;

public class InfixToPostfix {

	
	public boolean isOperand(char ch) {			// check if its Operand

		// accept numbers
		if (ch >= '0' && ch <= '9')
			return true;

		// accept lower cases
		if (ch >= 'a' && ch <= 'z')
			return true;

		// accept upper cases
		if (ch >= 'A' && ch <= 'Z')
			return true;

		return false;
	}

	
	public boolean isOperator(char ch) {			// check if its Operator

		if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
			return true;

		return false;
	}

		
	public int precedence(char op) {				// return precedence for an operator
		
		// The operators + and – have the same precedence.
		if (op == '+' || op == '-')
			return 1;

		// The operators * and / have the same precedence.
		// The operators * and / have a higher precedence
		// than the operators + and -.
		if (op == '*' || op == '/')
			return 2;

		// The arithmetic expression can contain parenthesis, ( and ).
		// Parenthesis have a higher precedence than the 4 operators.

		if (op == ')')
			return 3;
		
		if (op == '(')
			return 0; // left parenthesis exception (lowest)

		return -1; // all other not known operator

	}

	// convert infix to postfix
	// uses a stack to process the operators and parenthesis in the arithmetic
	// expression.
	// Treat the arithmetic expression as a linear sequence of tokens.
	// A token is an operand (positive integer or variable), an operator, or a
	// left or right parenthesis.

	public String convertToPostfix(String infix) {

		String postfix = ""; // store postfix expression here

		// Create an empty stack.
		Stack<Character> stk = new DynamicArrayStack<Character>();

		// From left to right, read and process each token in the arithmetic
		// expression one at a time.
		for (int i = 0; i < infix.length(); i++) {

			char token = infix.charAt(i);

			// Operand token: print the operand out right away.
			if (isOperand(token))
			{
				// insert with spacing
				if(postfix.length()==0 || postfix.charAt(postfix.length()-1) == ' ')
				    postfix += token;
				else 
					 postfix += " " + token;
		
				
				// get any more operands
				while(i < infix.length()-1 && isOperand(infix.charAt(i+1)))
				{
					postfix+=infix.charAt(++i);
				}
				
				postfix+=" "; // space 
			}

			// Operator token:
			else if (isOperator(token)) {
				
				// 1. If the stack is not empty and the operator at the top of
				// the stack has a higher or equal precedence than the operator
				// token just read,
				// then pop the operator at the top of the stack and print the
				// popped operator.

				while (!stk.isEmpty()
						&& precedence(stk.top()) >= precedence(token)) {
					char operator = stk.pop();
					
					// insert with spacing
					if(postfix.length()==0 || postfix.charAt(postfix.length()-1) == ' ')
					    postfix += operator;
					else
						 postfix += " " + operator;

					// 2. Repeat #1 until the stack is empty or the operator at
					// the top of the stack
					// has a lower precedence than the operator token just read,
					// then push the operator token
					// just read on top of the stack.
				}

				// Note: Even though left parenthesis has a higher precedence
				// than the other operators,
				// treat it as if it has the lowest precedence than all the
				// other operators.

				// push token operator on stack
				stk.push(token);
			}

			// Left Parenthesis token:
			else if (token == '(')

				stk.push(token); // Push the left parenthesis on top of the
									// stack.

			// Right parenthesis token:
			else if (token == ')') {
				// Pop the operator at the top of the stack and print the popped
				// operator
				// until the top of the stack contains a left parenthesis.
				while (stk.top() != '(') {
					token = stk.pop();
					
					// insert with spacing
					if(postfix.length()==0 || postfix.charAt(postfix.length()-1) == ' ')
					    postfix += token;
					else
						 postfix += " " + token;
				}

				// Pop the left parenthesis at the top of the stack and discard
				// it.
				stk.pop();
			}

		}

		// After the last token in the arithmetic expression is read and
		// processed,
		// pop the operator at the top of the stack and print the popped
		// operator until the stack is empty.
		while (!stk.isEmpty()) {
			char token = stk.pop();

			// insert with spacing
			if(postfix.length() == 0 || postfix.charAt(postfix.length()-1) == ' ')
			    postfix += token;
			else
				 postfix += " " + token;
		}

		return postfix; // return postfix expression
	}
}
