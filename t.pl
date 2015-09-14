sub  trim { my $s = shift; $s =~ s/^\s+|\s+$//g; return $s };

my $tokens_str = 
'
           | ( | ) | , | _num | _str | _subs | $
';

my $in =
"
-----------+---+---+---+------+------+-------+---
  [(, C]   |   |   | S |      |  S   |       |   |
-----------+---+---+---+------+------+-------+---
  [), C]   |   |   |   |      |      |       | R |
-----------+---+---+---+------+------+-------+---
  [,, C]   |   | S | S |  S   |      |       |   |
-----------+---+---+---+------+------+-------+---
[_num, C]  |   | R | R |      |      |       |   |
-----------+---+---+---+------+------+-------+---
[_str, C]  |   |   | R |      |      |       |   |
-----------+---+---+---+------+------+-------+---
[_subs, C] | S |   |   |      |      |       |   |
-----------+---+---+---+------+------+-------+---
   [#]     |   |   |   |      |      |   S   |   |
-----------+---+---+---+------+------+-------+---
[#, SUBOP] |   |   |   |      |      |   S   | A |
";

my @captures = $tokens_str =~ /\s+(?:\|\s(.+?)\s)(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?(?:\|\s(.+?)\s)?/g;
my @tokens = map { trim($_) } @captures;
@tokens = grep { $_ ne "" } @tokens;

@tokens = map { uc $_ } @tokens;
@tokens = map { if ($_ =~ /^#/) {"_HASH"} elsif ($_ eq 'S') {'_S'} elsif ($_ eq 'A') {'_A'} elsif ($_ eq 'R') {'_R'} elsif ($_ eq '$') {'_EPS'} elsif ($_ eq '.') {"_DOT"} elsif ($_ eq '=') {"_RAVNO"} elsif ($_ eq '(') {"_OBRACK"} elsif ($_ eq ')') {"_CBRACK"} elsif ($_ eq ';') {"_SEMCOL"} elsif ($_ eq ':') {"_COLUM"} elsif ($_ eq ',') {"_COMMA"} elsif ($_ eq '') {"_E"} elsif ($_ eq '+') {"_PLUS"} elsif ($_ eq '-') {"_MINUS"} elsif ($_ eq '*') {"_MULT"} elsif ($_ eq '/') {"_DIV"} else {$_} } @tokens;

print join(" !!! ", @tokens) . "\n";
my $count = @tokens;

my @lines = split /\n/, $in;
foreach my $line (@lines) {
    if ($line =~ /^-/) {
        next;
    }
    else {
        my @capts = $line =~ /\s*\[(.+?)\]\s+\|(?:(.+?)\|)(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?(?:(.+?)\|)?/g;
        my @capts = grep { $_ ne "" } @capts;
        @capts = map { trim($_) } @capts;
        @capts = map { uc $_ } @capts;
        @capts = map { if ($_ =~ /^#(.*)/) {"_HASH$1"} elsif ($_ eq 'S') {'_S'} elsif ($_ eq 'A') {'_A'} elsif ($_ eq 'C') {'_C'} elsif ($_ eq 'R') {'_R'} elsif ($_ eq '$') {'_EPS'} elsif ($_ eq '.') {"_DOT"} elsif ($_ eq '=') {"_RAVNO"} elsif ($_ eq '(') {"_OBRACK"} elsif ($_ eq ')') {"_CBRACK"} elsif ($_ eq ';') {"_SEMCOL"} elsif ($_ eq ':') {"_COLUM"} elsif ($_ eq ',') {"_COMMA"} elsif ($_ eq '') {"_E"} elsif ($_ eq '+') {"_PLUS"} elsif ($_ eq '-') {"_MINUS"} elsif ($_ eq '*') {"_MULT"} elsif ($_ eq '/') {"_DIV"} else {$_} } @capts;
        
        my @instack = split /, /, $capts[0];
        @instack = map { uc $_ } @instack;
        @instack = map { if ($_ =~ /^#/) {"_HASH"} elsif ($_ eq 'S') {'_S'} elsif ($_ eq 'A') {'_A'} elsif ($_ eq 'C') {'_C'} elsif ($_ eq 'R') {'_R'} elsif ($_ eq '$') {'_EPS'} elsif ($_ eq '.') {"_DOT"} elsif ($_ eq '=') {"_RAVNO"} elsif ($_ eq '(') {"_OBRACK"} elsif ($_ eq ')') {"_CBRACK"} elsif ($_ eq ';') {"_SEMCOL"} elsif ($_ eq ':') {"_COLUM"} elsif ($_ eq ',') {"_COMMA"} elsif ($_ eq '') {"_E"} elsif ($_ eq '+') {"_PLUS"} elsif ($_ eq '-') {"_MINUS"} elsif ($_ eq '*') {"_MULT"} elsif ($_ eq '/') {"_DIV"} else {$_} } @instack;
        
        my $s = "struct TransRule tr; ";
        foreach my $ins (@instack) {
            $s .= "tr.inStack.push_back($ins); ";
        }
        #print $s;
        if ($s eq "struct TransRule tr; ") {next;}
        
        my $i = 1;
        foreach my $tok (@tokens) {
            my $rs = "    { " . $s . "tr.input = $tok; tr.rule = " . @capts[$i] . ";";
            $i++;
            $rs .= " g.transRules.push_back(tr); }\n";
            print $rs;
        }
        print "\n";
    }
}
