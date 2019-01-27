<?PHP

$steps = 3;

echo 'GIMP Palette
Name: StepMap-'.$steps.'
Columns: 0
#
';
/*     0  64   0	Unbenannt   */

$sc=array(0);
$c = 0xFF;

for($steps; $steps>0; $steps--) {
    $sc[] = round($c);
    $c/=2;
}
sort($sc);

foreach($sc as $r) {
    foreach($sc as $g) {
        foreach($sc as $b) {
        
            printf("%1$ 3d %2$ 3d %3$ 3d\tUnbenannt\n", $r, $g, $b);
        }
    }
}

?>
