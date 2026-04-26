
; make code faser
OPTIMIZE_SEQUENCE_FORMATS = 1 

; make code slower
UNROLL_STRING_SEARCH_SMALL_LOOP = 0 
USE_AVX_INTEGER_PRINT = 0

; unknown
COMPRESS_SMALL_PRECISION_E_FLOAT = 1 ; not decrease precision, but cut numer size if there is too small count of digits after . in E format

; make code ?slower? but more cstdlib compactable
STRICT_GNU = 0

; xprintf only
BUFFER_SIZE = 10*1024
