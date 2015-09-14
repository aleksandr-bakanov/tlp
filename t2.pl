sub  trim { my $s = shift; $s =~ s/^\s+|\s+$//g; return $s };

my $in =
"
-------------------------------------------+----------
# [_subs, (, SUBOP, ,, SUBOP, ,, SUBOP, )] | 0, SUBOP
-------------------------------------------+----------
                 , [_num]                  | 2, SUBOP
-------------------------------------------+----------
                 ( [_str]                  | 4, SUBOP
";

my @lines = split /\n/, $in;
foreach my $line (@lines) {
    if ($line =~ /^-/ or $line =~ /^$/) {
        next;
    }
    else {
        my @capts = $line =~ /\s*(.+?)\s\[(.+?)\]\s+\|\s(.).+$/g;
        #my @capts = grep { $_ ne "" } @capts;
        #@capts = map { trim($_) } @capts;
        @capts = map { uc $_ } @capts;
        @capts = map { if ($_ =~ /^#(.*)/) {"_HASH$1"} elsif ($_ eq 'S') {'_S'} elsif ($_ eq 'A') {'_A'} elsif ($_ eq 'C') {'_C'} elsif ($_ eq 'R') {'_R'} elsif ($_ eq '$') {'_EPS'} elsif ($_ eq '.') {"_DOT"} elsif ($_ eq '=') {"_REL"} elsif ($_ eq '(') {"_OBRACK"} elsif ($_ eq ')') {"_CBRACK"} elsif ($_ eq ';') {"_SEMCOL"} elsif ($_ eq ':') {"_COLUM"} elsif ($_ eq ',') {"_COMMA"} elsif ($_ eq '') {"_E"} elsif ($_ eq '+') {"_PLUS"} elsif ($_ eq '-') {"_MINUS"} elsif ($_ eq '*') {"_MULT"} elsif ($_ eq '/') {"_DIV"} else {$_} } @capts;
        
        my @instack = split /, /, $capts[1];
        @instack = map { uc $_ } @instack;
        @instack = map { if ($_ =~ /^#/) {"_HASH"} elsif ($_ eq 'S') {'_S'} elsif ($_ eq 'A') {'_A'} elsif ($_ eq 'C') {'_C'} elsif ($_ eq 'R') {'_R'} elsif ($_ eq '$') {'_EPS'} elsif ($_ eq '.') {"_DOT"} elsif ($_ eq '=') {"_REL"} elsif ($_ eq '(') {"_OBRACK"} elsif ($_ eq ')') {"_CBRACK"} elsif ($_ eq ';') {"_SEMCOL"} elsif ($_ eq ':') {"_COLUM"} elsif ($_ eq ',') {"_COMMA"} elsif ($_ eq '') {"_E"} elsif ($_ eq '+') {"_PLUS"} elsif ($_ eq '-') {"_MINUS"} elsif ($_ eq '*') {"_MULT"} elsif ($_ eq '/') {"_DIV"} else {$_} } @instack;
        
        
        my $s = "    { struct FoldRule fr; ";
        $s .= "fr.inStack.push_back($capts[0]); ";
        foreach my $ins (@instack) {
            $s .= "fr.inStack.push_back($ins); ";
        }
        $s .= "fr.ruleNum = $capts[2]; ";
        $s .= "g.foldRules.push_back(fr); }\n";
        print $s;
    }
}
