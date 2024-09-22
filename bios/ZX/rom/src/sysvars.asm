; ================
; System Variables
; ================

; --------------------
; New System Variables
; --------------------
; These are held in the old ZX Printer buffer at $5B00-$5BFF.
; Note that some of these names conflict with the system variables used by the ZX Interface 1.

SWAP        EQU $5B00  ; 20   Swap paging subroutine.
YOUNGER     EQU $5B14  ;  9   Return paging subroutine.
ONERR       EQU $5B1D  ; 18   Error handler paging subroutine.
PIN         EQU $5B2F  ;  5   RS232 input pre-routine.
POUT        EQU $5B34  ; 22   RS232 token output pre-routine. This can be patched to bypass the control code filter.
POUT2       EQU $5B4A  ; 14   RS232 character output pre-routine.
TARGET      EQU $5B58  ;  2   Address of subroutine to call in ROM 1.
RETADDR     EQU $5B5A  ;  2   Return address in ROM 0.
BANK_M      EQU $5B5C  ;  1   Copy of last byte output to I/O port $7FFD.
RAMRST      EQU $5B5D  ;  1   Stores instruction RST $08 and used to produce a standard ROM error.
RAMERR      EQU $5B5E  ;  1   Error number for use by RST $08 held in RAMRST.
BAUD        EQU $5B5F  ;  2   Baud rate timing constant for RS232 socket. Default value of 11. [Name clash with ZX Interface 1 system variable at $5CC3]
SERFL       EQU $5B61  ;  2   Second character received flag:
                       ;        Bit 0   : 1=Character in buffer.
                       ;        Bits 1-7: Not used (always hold 0).
              ; $5B62  ;      Received Character.
COL         EQU $5B63  ;  1   Current column from 1 to WIDTH.
WIDTH       EQU $5B64  ;  1   Paper column width. Default value of 80. [Name clash with ZX Interface 1 Edition 2 system variable at $5CB1]
TVPARS      EQU $5B65  ;  1   Number of inline parameters expected by RS232 (e.g. 2 for AT).
FLAGS3      EQU $5B66  ;  1   Flags: [Name clashes with the ZX Interface 1 system variable at $5CB6]
                       ;        Bit 0: 1=BASIC/Calculator mode, 0=Editor/Menu mode.
                       ;        Bit 1: 1=Auto-run loaded BASIC program. [Set but never tested by the ROM]
                       ;        Bit 2: 1=Editing RAM disk catalogue.
                       ;        Bit 3: 1=Using RAM disk commands, 0=Using cassette commands.
                       ;        Bit 4: 1=Indicate LOAD.
                       ;        Bit 5: 1=Indicate SAVE.
                       ;        Bit 6; 1=Indicate MERGE.
                       ;        Bit 7: 1=Indicate VERIFY.
N_STR1      EQU $5B67  ; 10   Used by RAM disk to store a filename. [Name clash with ZX Interface 1 system variable at $5CDA]
                       ;      Used by the renumber routine to store the address of the BASIC line being examined.
HD_00       EQU $5B71  ;  1   Used by RAM disk to store file header information (see RAM disk Catalogue section below for details). [Name clash with ZX Interface 1 system variable at $5CE6]
                       ;      Used as column pixel counter in COPY routine.
                       ;      Used by FORMAT command to store specified baud rate.
                       ;      Used by renumber routine to store the number of digits in a pre-renumbered line number reference. [Name clash with ZX Interface 1 system variable at $5CE7]
HD_0B       EQU $5B72  ;  2   Used by RAM disk to store header info - length of block.
                       ;      Used as half row counter in COPY routine.
                       ;      Used by renumber routine to generate ASCII representation of a new line number.
HD_0D       EQU $5B74  ;  2   Used by RAM disk to store file header information (see RAM disk Catalogue section below for details). [Name clash with ZX Interface 1 system variable at $5CE9]
HD_0F       EQU $5B76  ;  2   Used by RAM disk to store file header information (see RAM disk Catalogue section below for details). [Name clash with ZX Interface 1 system variable at $5CEB]
                       ;      Used by renumber routine to store the address of a referenced BASIC line.
HD_11       EQU $5B78  ;  2   Used by RAM disk to store file header information (see RAM disk Catalogue section below for details). [Name clash with ZX Interface 1 system variable at $5CED]
                       ;      Used by renumber routine to store existing VARS address/current address within a line.
SC_00       EQU $5B7A  ;  1   Used by RAM disk to store alternate file header information (see RAM disk Catalogue section below for details).
SC_0B       EQU $5B7B  ;  2   Used by RAM disk to store alternate file header information (see RAM disk Catalogue section below for details).
SC_0D       EQU $5B7D  ;  2   Used by RAM disk to store alternate file header information (see RAM disk Catalogue section below for details).
SC_0F       EQU $5B7F  ;  2   Used by RAM disk to store alternate file header information (see RAM disk Catalogue section below for details).
OLDSP       EQU $5B81  ;  2   Stores old stack pointer when TSTACK in use.
SFNEXT      EQU $5B83  ;  2   End of RAM disk catalogue marker. Pointer to first empty catalogue entry.
SFSPACE     EQU $5B85  ;  3   Number of bytes free in RAM disk (3 bytes, 17 bit, LSB first).
ROW01       EQU $5B88  ;  1   Stores keypad data for row 3, and flags:
                       ;        Bit 0   : 1=Key '+' pressed.
                       ;        Bit 1   : 1=Key '6' pressed.
                       ;        Bit 2   : 1=Key '5' pressed.
                       ;        Bit 3   : 1=Key '4' pressed.
                       ;        Bits 4-5: Always 0.
                       ;        Bit 6   : 1=Indicates successful communications to the keypad.
                       ;        Bit 7   : 1=If communications to the keypad established.
ROW23       EQU $5B89  ;  1   Stores keypad key press data for rows 1 and 2:
                       ;        Bit 0: 1=Key ')' pressed.
                       ;        Bit 1: 1=Key '(' pressed.
                       ;        Bit 2: 1=Key '*' pressed.
                       ;        Bit 3: 1=Key '/' pressed.
                       ;        Bit 4: 1=Key '-' pressed.
                       ;        Bit 5: 1=Key '9' pressed.
                       ;        Bit 6: 1=Key '8' pressed.
                       ;        Bit 7: 1=Key '7' pressed.
ROW45       EQU $5B8A  ;  1   Stores keypad key press data for rows 4 and 5:
                       ;        Bit 0: Always 0.
                       ;        Bit 1: 1=Key '.' pressed.
                       ;        Bit 2: Always 0.
                       ;        Bit 3: 1=Key '0' pressed.
                       ;        Bit 4: 1=Key 'ENTER' pressed.
                       ;        Bit 5: 1=Key '3' pressed.
                       ;        Bit 6: 1=Key '2' pressed.
                       ;        Bit 7: 1=Key '1' pressed.
SYNRET      EQU $5B8B  ;  2   Return address for ONERR routine.
LASTV       EQU $5B8D  ;  5   Last value printed by calculator.
RNLINE      EQU $5B92  ;  2   Address of the length bytes in the line currently being renumbered.
RNFIRST     EQU $5B94  ;  2   Starting line number when renumbering. Default value of 10.
RNSTEP      EQU $5B96  ;  2   Step size when renumbering. Default value of 10.
STRIP1      EQU $5B98  ; 32   Used as RAM disk transfer buffer (32 bytes to $5BB7).
                       ;      Used to hold Sinclair stripe character patterns (16 bytes to $5BA7).
                       ;      ...
TSTACK      EQU $5BFF  ;  n   Temporary stack (grows downwards). The byte at $5BFF is not actually used.