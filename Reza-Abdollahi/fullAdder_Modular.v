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

module test_fullAdder();
    reg x, y, cin;
    wire cout, sum;
    fullAdder test(.x(x), .y(y), .cin(cin), .cout(cout), .sum(sum));
    initial begin
        $monitor("x=%b, y=%b, cin=%b | cout=%b, sum=%b", x, y, cin, cout, sum);
        x = 1'b0;
        y = 1'b0;
        cin = 1'b0;
        #10
        cin = 1'b1;
        #10
        y = 1'b1;
        cin = 1'b0;
        #10
        cin = 1'b1;
        #10
        x = 1'b1;
        y = 1'b0;
        cin = 1'b0;
        #10
        cin = 1'b1;
        #10
        y = 1'b1;
        cin = 1'b0;
        #10
        cin = 1'b1;
    end
endmodule