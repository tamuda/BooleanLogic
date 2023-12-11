/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circuit.h"

static Circuit and3_Circuit() {

    char *title = "Two AND gates connected to make a 3-input AND circuit";

    // Create the inputs
    int NINPUTS = 3;
    Boolean x = new_Boolean(false);
    Boolean y = new_Boolean(false);
    Boolean z = new_Boolean(false);
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;

    // Create the outputs
    int NOUTPUTS = 1;
    Boolean result = new_Boolean(false);
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = result;

    // Create the gates
    int NGATES = 2;
    Gate A1 = new_AndGate();
    Gate A2 = new_AndGate();
    Gate* gates = new_Gate_array(NGATES);
    gates[0] = A1;
    gates[1] = A2;

    // Create the circuit
    Circuit circuit = new_Circuit(title,
				  NINPUTS, inputs,
				  NOUTPUTS, outputs,
				  NGATES, gates);

    // Connect the gates in the circuit
    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, y, Gate_getInput(A1, 1));
    Boolean x_and_y = Gate_getOutput(A1);

    Circuit_connect(circuit, x_and_y, Gate_getInput(A2, 0));
    Circuit_connect(circuit, z, Gate_getInput(A2, 1));
    Boolean x_and_y_and_z = Gate_getOutput(A2);

    Circuit_connect(circuit, x_and_y_and_z, result);

    // Done!
    return circuit;
}

// You should not use this function in your project.
// It is here to show you how to get and set values in a circuit using the API.
// See the project description for what you are required to do.
// Go to study session if you have questions about how to do it.
static void test3In1Out(Circuit circuit, bool in0, bool in1, bool in2) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_setInput(circuit, 2, in2);
    Circuit_update(circuit);
    printf("%s %s %s -> %s\n",
	   Boolean_toString(Circuit_getInput(circuit, 0)),
	   Boolean_toString(Circuit_getInput(circuit, 1)),
	   Boolean_toString(Circuit_getInput(circuit, 2)),
	   Boolean_toString(Circuit_getOutput(circuit, 0)));
}

static Circuit circuitA() {
    char *title = "Circuit with AND, OR, NOT, and AND gates";

    // Number of inputs, outputs, and gates
    int NINPUTS = 2;
    int NOUTPUTS = 1;
    int NGATES = 4;

    // Create the inputs
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = new_Boolean(false); // input x
    inputs[1] = new_Boolean(false); // input y

    // Create the outputs
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = new_Boolean(false); // output result

    // Create the gates
    Gate* gates = new_Gate_array(NGATES);
    gates[0] = new_AndGate(); // First AND gate
    gates[1] = new_OrGate();  // OR gate
    gates[2] = new_NotGate(); // NOT gate
    gates[3] = new_AndGate(); // Second AND gate (final output gate)

    // Create the circuit
    Circuit circuit = new_Circuit(title, NINPUTS, inputs, NOUTPUTS, outputs, NGATES, gates);

    // Connect the gates in the circuit
    // First AND gate with inputs x and y
    Circuit_connect(circuit, inputs[0], Gate_getInput(gates[0], 0));
    Circuit_connect(circuit, inputs[1], Gate_getInput(gates[0], 1));
    // OR gate with inputs x and y
    Circuit_connect(circuit, inputs[0], Gate_getInput(gates[1], 0));
    Circuit_connect(circuit, inputs[1], Gate_getInput(gates[1], 1));
    // NOT gate with output from the first AND gate
    Circuit_connect(circuit, Gate_getOutput(gates[0]), Gate_getInput(gates[2], 0));
    // Second AND gate with output from OR gate and output from NOT gate
    Circuit_connect(circuit, Gate_getOutput(gates[1]), Gate_getInput(gates[3], 0));
    Circuit_connect(circuit, Gate_getOutput(gates[2]), Gate_getInput(gates[3], 1));
    // Connect the output of the second AND gate to the circuit output
    Circuit_connect(circuit, Gate_getOutput(gates[3]), outputs[0]);

    // Return the circuit
    return circuit;
}

// Test function for the circuit
static void testCircuitA(Circuit circuit, bool in0, bool in1) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_update(circuit);
    printf("Input X: %s, Input Y: %s -> Result: %s\n",
           Boolean_toString(Circuit_getInput(circuit, 0)),
           Boolean_toString(Circuit_getInput(circuit, 1)),
           Boolean_toString(Circuit_getOutput(circuit, 0)));
}

// Circuit(b)
static Circuit circuitB() {
    char *title = "Circuit B with two NOR gates followed by a third NOR gate";

    // Number of inputs, outputs, and gates
    int NINPUTS = 2;
    int NOUTPUTS = 1;
    int NGATES = 3;

    // Create the inputs
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = new_Boolean(false); // input x
    inputs[1] = new_Boolean(false); // input y

    // Create the outputs
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = new_Boolean(false); // output result

    // Create the gates
    Gate* gates = new_Gate_array(NGATES);
    gates[0] = new_NorGate(); // First NOR gate
    gates[1] = new_NorGate(); // Second NOR gate
    gates[2] = new_NorGate(); // Third NOR gate that combines the first two

    // Create the circuit
    Circuit circuit = new_Circuit(title, NINPUTS, inputs, NOUTPUTS, outputs, NGATES, gates);

    // Connect the gates in the circuit
    // First NOR gate with inputs x and y
    Circuit_connect(circuit, inputs[0], Gate_getInput(gates[0], 0));
    Circuit_connect(circuit, inputs[1], Gate_getInput(gates[0], 1));
    // Second NOR gate with inputs x and y
    Circuit_connect(circuit, inputs[0], Gate_getInput(gates[1], 0));
    Circuit_connect(circuit, inputs[1], Gate_getInput(gates[1], 1));
    // Third NOR gate with outputs from the first and second NOR gates
    Circuit_connect(circuit, Gate_getOutput(gates[0]), Gate_getInput(gates[2], 0));
    Circuit_connect(circuit, Gate_getOutput(gates[1]), Gate_getInput(gates[2], 1));
    // Connect the output of the third NOR gate to the circuit output
    Circuit_connect(circuit, Gate_getOutput(gates[2]), outputs[0]);

    // Return the circuit
    return circuit;
}

// Test function for the circuit
static void testCircuitB(Circuit circuit, bool in0, bool in1) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_update(circuit);
    printf("Input X: %s, Input Y: %s -> Result: %s\n",
           Boolean_toString(Circuit_getInput(circuit, 0)),
           Boolean_toString(Circuit_getInput(circuit, 1)),
           Boolean_toString(Circuit_getOutput(circuit, 0)));
}

static Circuit circuitC() {
    char *title = "Circuit C with three OR gates and two AND gates";

    // Number of inputs, outputs, and gates
    int NINPUTS = 3;
    int NOUTPUTS = 1;
    int NGATES = 5;

    // Create the inputs
    Boolean* inputs = new_Boolean_array(NINPUTS);
    inputs[0] = new_Boolean(false); // input x
    inputs[1] = new_Boolean(false); // input y
    inputs[2] = new_Boolean(false); // input z

    // Create the outputs
    Boolean* outputs = new_Boolean_array(NOUTPUTS);
    outputs[0] = new_Boolean(false); // output result

    // Create the gates
    Gate* gates = new_Gate_array(NGATES);
    gates[0] = new_OrGate(); // OR gate for x and y
    gates[1] = new_OrGate(); // OR gate for y and z
    gates[2] = new_OrGate(); // OR gate for x and z
    gates[3] = new_AndGate(); // AND gate for outputs of OR gates 1 and 3
    gates[4] = new_AndGate(); // AND gate for output of AND gate 3 and OR gate 2

    // Create the circuit
    Circuit circuit = new_Circuit(title, NINPUTS, inputs, NOUTPUTS, outputs, NGATES, gates);

    // Connect the gates in the circuit
    // Connect inputs to the OR gates
    Circuit_connect(circuit, inputs[0], Gate_getInput(gates[0], 0));
    Circuit_connect(circuit, inputs[1], Gate_getInput(gates[0], 1));
    Circuit_connect(circuit, inputs[1], Gate_getInput(gates[1], 0));
    Circuit_connect(circuit, inputs[2], Gate_getInput(gates[1], 1));
    Circuit_connect(circuit, inputs[0], Gate_getInput(gates[2], 0));
    Circuit_connect(circuit, inputs[2], Gate_getInput(gates[2], 1));

    // Connect the outputs of the OR gates to the first AND gate
    Circuit_connect(circuit, Gate_getOutput(gates[0]), Gate_getInput(gates[3], 0));
    Circuit_connect(circuit, Gate_getOutput(gates[2]), Gate_getInput(gates[3], 1));

    // Connect the output of the first AND gate and the output of the second OR gate to the final AND gate
    Circuit_connect(circuit, Gate_getOutput(gates[3]), Gate_getInput(gates[4], 0));
    Circuit_connect(circuit, Gate_getOutput(gates[1]), Gate_getInput(gates[4], 1));

    // Connect the output of the final AND gate to the circuit output
    Circuit_connect(circuit, Gate_getOutput(gates[4]), outputs[0]);

    // Return the circuit
    return circuit;
}

// Test function for the circuit
static void testCircuitC(Circuit circuit, bool in0, bool in1, bool in2) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_setInput(circuit, 2, in2);
    Circuit_update(circuit);
    printf("Input X: %s, Input Y: %s, Input Z: %s -> Result: %s\n",
           Boolean_toString(Circuit_getInput(circuit, 0)),
           Boolean_toString(Circuit_getInput(circuit, 1)),
           Boolean_toString(Circuit_getInput(circuit, 2)),
           Boolean_toString(Circuit_getOutput(circuit, 0)));
}

int main(int argc, char **argv) {
    // Circuit circuit = and3_Circuit();
    // Circuit_dump(circuit);
    // printf("\n");
    // printf("Testing: Some input(s) false: should be false\n");
    // test3In1Out(circuit, true, true, false);
    // printf("Testing: All inputs true: should be true\n");
    // test3In1Out(circuit, true, true, true);
    // printf("\nNote: Your program needs a function that tests ANY circuit on ALL possible\ncombinations of input values, in order from all false to all true, per the\nproject description.\n");
    // free_Circuit(circuit);

    char circuitName[10];
    printf("Enter the name of the circuit you want to test: ");
    scanf("%s", circuitName);

    Circuit circuitInstance;

    if (strcmp(circuitName, "circuitA") == 0) {
        circuitInstance = circuitA();
    } else if (strcmp(circuitName, "circuitB") == 0) {
        circuitInstance = circuitB();
    } else if (strcmp(circuitName, "circuitC") == 0) {
        circuitInstance = circuitC();
    } else {
        printf("Invalid circuit name\n");
        return 1;
    }

    free_Circuit(circuitInstance);
    return 0;

    // Circuit circuit = circuitA();
    // Circuit_dump(circuit);
    // // Testing the circuit(a) with different inputs
    // printf("\nTesting Circuit A\n");
    // testCircuitA(circuit, false, false);
    // testCircuitA(circuit, false, true);
    // testCircuitA(circuit, true, false);
    // testCircuitA(circuit, true, true);

    // // Freeing the circuit
    // free_Circuit(circuit);

    // circuit = circuitB();
    // Circuit_dump(circuit);

    // // Testing the circuit with different inputs
    // printf("\nTesting Circuit B\n");
    // testCircuitB(circuit, false, false);
    // testCircuitB(circuit, false, true);
    // testCircuitB(circuit, true, false);
    // testCircuitB(circuit, true, true);

    // // Freeing the circuit
    // free_Circuit(circuit);

    //  circuit = circuitC();
    // Circuit_dump(circuit);

    // // Testing the circuit with different inputs
    // printf("\nTesting Circuit C\n");
    // testCircuitC(circuit, false, false, false);
    // testCircuitC(circuit, false, false, true);
    // testCircuitC(circuit, false, true, false);
    // testCircuitC(circuit, false, true, true);
    // testCircuitC(circuit, true, false, false);
    // testCircuitC(circuit, true, false, true);
    // testCircuitC(circuit, true, true, false);
    // testCircuitC(circuit, true, true, true);
    // // Freeing the circuit
    // free_Circuit(circuit);
    
}

    //create a general function that takes the name of a function and prints out all possible test cases for that function
    static void testAnyCircuit(CircuitFunction circuitFunction, const char* circuitName, int numInputs) {
        Circuit circuit = circuitFunction();
        Circuit_dump(circuit);

        printf("\nTesting %s\n", circuitName);

        int numTestCases = 1 << numInputs;

        for (int i = 0; i < numTestCases; i++) {
            for (int j = 0; j < numInputs; j++) {
                bool input = (i >> j) & 1;
                Circuit_setInput(circuit, j, input);
                printf("Input %d: %s\n", j, Boolean_toString(Circuit_getInput(circuit, j)));
            }

            Circuit_update(circuit);
            printf("-> Result: %s\n", Boolean_toString(Circuit_getOutput(circuit, 0)));
        }

        free_Circuit(circuit);
    }
    //create a function that takes a circuit and prints out all possible test cases for that circuit
