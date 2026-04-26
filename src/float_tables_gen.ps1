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

$data, $divisors = 1..2 | % -parallel {
    [pscustomobject]@{index=$_; value=$(switch ($_) {
        1 {
            # create float -> int table
            
            # to calculate you need $m * $multipler / $scale   *   10 ^ $d
            
            1..0x7FE | % {
                Write-Progress -Id 1 -Activity "Generating float -> int tables" -Status "..." -PercentComplete ([int](100*$_/0x7FE))
                $e = $_ - 1023n - 52n
                -310..310 | % {
                    $d = [bigint]$_
                    $multipler = $using:scale
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
            Write-Progress -Id 1 -Activity "Generating float -> int tables" -Completed
        }
        2 {
            # function g([bigint]$x,[bigint]$m, [bigint]$s){$r=($x*$m)-shr64n;$t=(($x-$r)-shr1n) + $r;$t-shr($s)}
            # create division on 10 table
            1..18 | % {
                $d = [bigint]::pow(10n, $_)
                $n = 64n
                0..[int]$n | % {
                    $l = $n + [bigint]$_
                    $m = ((1n-shl$l) + $d - (1n-shl$l)%$d) / $d
                    $mLow = $m - (1n-shl$n)
                    if (0n -le $mLow -and $mLow -lt (1n-shl$n))
                    {
                        [pscustomobject]@{multipler=$mLow; shift=$_-1n}
                    }
                } | select -First 1
                Write-Progress -Id 2 -Activity "Generating division on 10 tables" -Status "..." -PercentComplete ([int](100*$_/18))
                sleep 0.2
            }
            Write-Progress -Id 2 -Activity "Generating division on 10 tables" -Completed
        }
    })}
} | sort-object index | % { Write-Output -NoEnumerate $_.value }

Write-Host "Data Gathered" -Fore green

@"

integer_numbers:
    db "$((0..99|%{([string]$_).PadLeft(2)-replace" ",0})-join"")"

float_table_multiplers:
$(($data | % {" "*4 + "dq $($_.multipler)"})-join"`n")

float_table_powers:
$(($data | % {" "*4 + "dw $($_.power)"})-join"`n")

div_10_pow_multiplers:
$(($divisors | % {" "*4 + "dq $($_.multipler)"})-join"`n")

div_10_pow_shifts:
$(($divisors | % {" "*4 + "db $($_.shift)"})-join"`n")

"@ >"$PSScriptRoot/float_tables.inc"

Write-Host "Generated" -Fore green
