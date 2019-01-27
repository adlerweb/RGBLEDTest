<?php

    $finput = 'test-indexed.h';
	$interleave = 16;
	$colorsteps = 3;

	//For everything else than 64x32 16S you might need to modify things below

	//EO Config

    $input = file_get_contents($finput);

	$x = (int)preg_match_single('/static unsigned int width = (\d+);/', $input);
	if(!$x) die('Image width not found'.PHP_EOL);
    echo '[D] Image width: '.$x.PHP_EOL;

	$y = (int)preg_match_single('/static unsigned int height = (\d+);/', $input);
	if(!$y) die('Image height not found'.PHP_EOL);
    echo '[D] Image height: '.$y.PHP_EOL;

	$header = get_img_header($input);
	$data = get_img_data($input, $x);

	$out = '/* Generated RGB LED Matrix image data. Source: '.$finput.' */'.str_repeat(PHP_EOL, 3);
    for($s=1; $s <= $colorsteps; $s++) {
		for($i=0; $i<$interleave; $i++) {
			$out .= 'const byte line_'.$i.'_s'.$s.'[] PROGMEM = {'.PHP_EOL;
			for($j=0; $j<$x; $j++) {
				$dl=0;
				$dl |= calccolor($data[$i+$interleave][$j], $s, $header);
				$dl <<= 3;
				$dl |= calccolor($data[$i][$j], $s, $header);
				$out .= sprintf('    0b%08b,'.PHP_EOL, $dl);
			}
			$out .= '};'.PHP_EOL;
		}
	}

	file_put_contents($finput.'.rgbdata.h', $out);

exit();

	function get_img_data($input, $x) {
		$hdr = preg_match_single('/static char header_data\[\] = \{(.+)\};/s', $input);
		unset($input);
		if(!$hdr) die('Data not found #1'.PHP_EOL);
		
		$hdr = explode(',', $hdr);

		$xn = 0;
		$out = array();
		$lout = array();
		for($i=0; $i<count($hdr); $i++) {
			if(($i % $x) == 0) {
				if(count($lout) > 0) $out[] = $lout;
				$lout = array();
			}
			$lout[] = (int)trim($hdr[$i]);
		}
		if(count($lout) > 0) $out[] = $lout;

		return $out;
	}

	function get_img_header($input) {
		$hdr = preg_match_single('/static char header_data_cmap\[\d+\]\[\d+\] = \{(.+)\};/s', $input);
		unset($input);
		if(!$hdr) die('Color header not found #1'.PHP_EOL);
		$chk = preg_match_all('/\{\s*(\d+),\s*(\d+),\s*(\d+)\}/', $hdr, $match);
		if(!$chk) die('Color header not found #2'.PHP_EOL);
		
		$out = array();
		for($i=0; $i<count($match[0]); $i++) {
			$out[] = array($match[1][$i], $match[2][$i], $match[3][$i]);
		}

		return $out;
	}

    function preg_match_single($regex, $input) {
        $chk = preg_match($regex, $input, $match);
        if(!$chk) return false;
        return $match[1];
    }

	function passtoi($num) {
		$color = 0xFF;
		for($i=0; $i<$num; $i++) $color/=2;
		$color = round($color);
		return $color;
	}

	function calccolor($data, $pass, $colormap) {
		$out = 0;
		$data = $colormap[$data];

		if($data[0] > passtoi($pass)) {
			$out |= 0b001;
		}
		if($data[1] > passtoi($pass)) {
			$out |= 0b010;
		}
		if($data[2] > passtoi($pass)) {
			$out |= 0b100;
		}

		return $out;
	}
?>
