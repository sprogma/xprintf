<#

    need:
        m * 2^e = x * 10^y

        x = m * 2^e / 10^y

    find biggest
#>

Write-Host "Starting" -Fore green

$scale = [bigint]::pow(2n, 64) # top 64 bits

$value = 17.957

$bits = [BitConverter]::DoubleToInt64Bits($value)

$exponent = ($bits -shr 52) -band 0x7FF
$mantissa = $bits -band 0xFFFFFFFFFFFFF

$exponent = 0x1
$mantissa = 4.94065645841246544177e-324


$m = $mantissa + (1n-shl52n)
$e = $exponent - 1023n - 52n
-310..310 | % {
    $d = $_
    $multipler = $scale
    ($e -ge 0 ? 1..0 : 0..1) | % {
        switch ($_) {
            0 {
                if ($d -ge 0) { $multipler /= [bigint]::pow(10n, $d) }
                         else { $multipler *= [bigint]::pow(10n, -$d) }
            } 1 {
                if ($e -ge 0) { $multipler *= [bigint]::pow(2n, $e) }
                         else { $multipler /= [bigint]::pow(2n, -$e) }
            }
        }
    }
    [pscustomobject]@{multipler=$multipler; power=$d}
} | ? { $_.multipler -le [ulong]::MaxValue }
  | select -First 1 | % {
    Write-Host "Found: multipler: " ($_.multipler)
    Write-Host "Found:     value: " ($m * $_.multipler / $scale) " * 10 ^ " $_.power
    Write-Host "Found:      real: " ([double]$m * (pow 2 $e))
}
  
# use 2^e

$data = 1..0x7FE | % {
    Write-Progress -Activity "Generating tables" -Status "..." -PercentComplete ([int](100*$_/0x7FE))
    $e = $_ - 1023n - 52n
    -310..310 | % {
        $d = $_
        $multipler = $scale
        ($e -ge 0 ? 1..0 : 0..1) | % {
            switch ($_) {
                0 {
                    if ($d -ge 0) { $multipler /= [bigint]::pow(10n, $d) }
                             else { $multipler *= [bigint]::pow(10n, -$d) }
                } 1 {
                    if ($e -ge 0) { $multipler *= [bigint]::pow(2n, $e) }
                             else { $multipler /= [bigint]::pow(2n, -$e) }
                }
            }
        }
        [pscustomobject]@{multipler=$multipler; power=$d}
    } | ? { $_.multipler -le [ulong]::MaxValue }
      | select -First 1
}

Write-Host "Data Gathered" -Fore green

@"

float_table_multiplers:
$(($data | % {" "*4 + "dq $($_.multipler)"})-join"`n")

float_table_powers:
$(($data | % {" "*4 + "dw $($_.power)"})-join"`n")

"@ >"$PSScriptRoot/float_tables.inc"

Write-Host "Generated" -Fore green

# to calculate you need $m * $multipler / $scale   *   10 ^ $d
