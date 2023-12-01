module halfAdder(
    x, y, cout, sum
);
    input x, y;
    output cout, sum;
    xor(sum, x, y);
    and(cout, x, y);
endmodule

module fullAdder(
    x, y, cin, cout, sum
);
    input x, y, cin;
    output cout, sum;
    wire cout1, cout2, sum1;
    halfAdder ha1(.x(cin), .y(x), .cout(cout1), .sum(sum1));
    halfAdder ha2(.x(sum1), .y(y), .cout(cout2), .sum(sum));
    or(cout, cout1, cout2);
endmodule

module fullAdder_8bit(
    x, y, cin, cout, sum
);
    input [7:0] x, y;
    input cin;
    output cout;
    output [7:0] sum;
    wire w0, w1, w2, w3, w4, w5, w6;
    fullAdder fa0(.x(x[0]), .y(y[0]), .cin(cin), .cout(w0), .sum(sum[0]));
    fullAdder fa1(.x(x[1]), .y(y[1]), .cin(w0), .cout(w1), .sum(sum[1]));
    fullAdder fa2(.x(x[2]), .y(y[2]), .cin(w1), .cout(w2), .sum(sum[2]));
    fullAdder fa3(.x(x[3]), .y(y[3]), .cin(w2), .cout(w3), .sum(sum[3]));
    fullAdder fa4(.x(x[4]), .y(y[4]), .cin(w3), .cout(w4), .sum(sum[4]));
    fullAdder fa5(.x(x[5]), .y(y[5]), .cin(w4), .cout(w5), .sum(sum[5]));
    fullAdder fa6(.x(x[6]), .y(y[6]), .cin(w5), .cout(w6), .sum(sum[6]));
    fullAdder fa7(.x(x[7]), .y(y[7]), .cin(w6), .cout(cout), .sum(sum[7]));
endmodule

module test_fullAdder_8bit();
    reg [7:0] x, y;
    reg cin;
    wire cout;
    wire [8:0] sum; // 9 bits to show overflow
    fullAdder_8bit test(.x(x), .y(y), .cin(cin), .cout(cout), .sum(sum));
    initial begin
        //-- Use %d for decimal and %b for binary
        $monitor("x=%d, y=%d, cin=%b | cout=%b, sum=%d", x, y, cin, cout, sum);
        x = 8'b11010111;
        y = 8'b10110101;
        cin = 1'b0;
        #10
        cin = 1'b1;
        #10
        x = 8'b00000111;
        y = 8'b00000101;
        cin = 1'b0;
        #10
        cin = 1'b1;
    end