{ NOTE: it is recommended to use this even if you don't understand the following code. }

{ constraints }
const
    MAXD = 1000;

{ input data }
var
    C, D, Y, i  : longint;
    // Warning! M and P are 1-based
    M, P        : array[1..MAXD] of longint;

begin
{
    uncomment the following lines if you want to read/write from files
    assign(input,  'input.txt');  reset(input);
    assign(output, 'output.txt'); rewrite(output);
}

    readln(C, D, Y);
    // Warning! M and P are 1-based
    for i:=1 to D do
        read(M[i]);
    readln();
    for i:=1 to D do
        read(P[i]);
    readln();

    { insert your code here }

    writeln(42); { print result }
end.
