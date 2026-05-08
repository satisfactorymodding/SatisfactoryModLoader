#!/usr/bin/env bash
# =============================================================================
# Scripts/audit_bugs.sh
# Exhaustive mechanical bug-pattern audit for all 4 owner mods.
#
# Usage:
#   cd <repo-root>
#   bash Scripts/audit_bugs.sh
#
# Exit code: 0 = no issues found, 1 = one or more issues found.
#
# Each check is applied to EVERY source file in all 4 mods so that a pattern
# fixed in one file is automatically verified across the entire codebase.
# This prevents the class of miss where a bug is caught in the first file
# encountered but identical code in other files goes unnoticed.
# =============================================================================

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
MOD_ROOT="$REPO_ROOT/Mods"

# Directories that contain owner-authored code (excludes SML/Alpakit/etc.)
OWNER_MODS=(
    "$MOD_ROOT/BanChatCommands/Source"
    "$MOD_ROOT/BanSystem/Source"
    "$MOD_ROOT/DiscordBridge/Source"
    "$MOD_ROOT/SMLWebSocket/Source"
)

RED='\033[0;31m'
YEL='\033[0;33m'
GRN='\033[0;32m'
NC='\033[0m'

ISSUES=0

# Helper: print a finding and increment the counter.
fail() {
    local check="$1"; shift
    echo -e "${RED}[FAIL]${NC} ${YEL}${check}${NC}"
    while [[ $# -gt 0 ]]; do
        echo "       $1"; shift
    done
    echo
    ISSUES=$((ISSUES + 1))
}

pass() {
    echo -e "${GRN}[PASS]${NC} $1"
}

# Build a single grep path list from all owner mod source directories.
MOD_PATHS=()
for d in "${OWNER_MODS[@]}"; do
    if [[ -d "$d" ]]; then
        MOD_PATHS+=("$d")
    fi
done

list_cpp_files() {
    [[ ${#MOD_PATHS[@]} -gt 0 ]] || return 0
    find "${MOD_PATHS[@]}" -name "*.cpp" -print0 2>/dev/null
}

list_header_files() {
    [[ ${#MOD_PATHS[@]} -gt 0 ]] || return 0
    find "${MOD_PATHS[@]}" -name "*.h" -print0 2>/dev/null
}

list_source_files() {
    [[ ${#MOD_PATHS[@]} -gt 0 ]] || return 0
    find "${MOD_PATHS[@]}" \( -name "*.cpp" -o -name "*.h" \) -print0 2>/dev/null
}

echo "========================================================"
echo " DiscordBridge bug-pattern audit"
echo " Scanning ${#MOD_PATHS[@]} mod source tree(s)"
echo "========================================================"
echo

echo " Files queued for scan:"
found_any=0
while IFS= read -r -d '' file; do
    echo "  - $file"
    found_any=1
done < <(list_source_files | sort -z)

if [[ "$found_any" -eq 0 ]]; then
    echo "  (none)"
fi

echo

# =============================================================================
# CHECK 1: INT64_MAX guard on NextId increment
#
# Pattern: any "NextId = <expr>.Id + 1" without the guard
# "(E.Id < INT64_MAX) ? E.Id + 1 : E.Id" (or equivalent).
#
# When a file has "NextId = X.Id + 1" but NOT the INT64_MAX guard string, it
# is a potential overflow.  We look for the plain increment pattern and then
# verify the guard is present in the same file.
# =============================================================================
echo "--- CHECK 1: INT64_MAX guard on all NextId increment loops ---"

while IFS= read -r -d '' file; do
    # Does this file contain an unguarded "= X.Id + 1" NextId assignment?
    if grep -qP '\bNextId\s*=\s*\(?\w+\.Id\s*\+\s*1' "$file"; then
        # Good only if the INT64_MAX guard is present somewhere in the file.
        if ! grep -qP 'INT64_MAX' "$file"; then
            fail "CHECK 1 – INT64_MAX guard" \
                "File: $file" \
                "Has 'NextId = X.Id + 1' but no INT64_MAX guard." \
                "Fix: wrap the increment:  NextId = (X.Id < INT64_MAX) ? X.Id + 1 : X.Id;"
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 1 done"
echo

# =============================================================================
# CHECK 2: Temp file cleanup on IFileManager::Move() failure
#
# Every SaveToFile() that does:
#   1. FFileHelper::SaveStringToFile(..., *TmpPath, ...)
#   2. IFileManager::Get().Move(*Dest, *TmpPath, ...)
# must also call IFileManager::Get().Delete(*TmpPath) in the failure branch.
#
# Strategy: find every file that calls both SaveStringToFile and Move.
# Then verify that Delete(*TmpPath) also appears (even if on the happy path
# the Move succeeds, the error branch must clean up).
# =============================================================================
echo "--- CHECK 2: Temp file cleanup after IFileManager::Move() failure ---"

while IFS= read -r -d '' file; do
    has_save=$(grep -cP 'SaveStringToFile' "$file")
    has_move=$(grep -cP 'IFileManager::Get\(\)\.Move' "$file")
    if [[ "$has_save" -gt 0 && "$has_move" -gt 0 ]]; then
        has_delete=$(grep -cP 'IFileManager::Get\(\)\.Delete' "$file")
        if [[ "$has_delete" -eq 0 ]]; then
            fail "CHECK 2 – temp file cleanup" \
                "File: $file" \
                "Uses SaveStringToFile + Move but has no IFileManager::Get().Delete() call." \
                "Fix: add IFileManager::Get().Delete(*TmpPath) in the Move failure branch."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 2 done"
echo

# =============================================================================
# CHECK 3: FDateTime::ParseIso8601 return value checked
#
# Every call to FDateTime::ParseIso8601() must use its bool return value.
# Bare "FDateTime::ParseIso8601(...)" (without assigning or checking the bool)
# silently leaves the output FDateTime unchanged on malformed input.
# =============================================================================
echo "--- CHECK 3: FDateTime::ParseIso8601() return value not ignored ---"

while IFS= read -r -d '' file; do
    # A call is "unchecked" when ParseIso8601 appears at the start of a
    # statement (i.e., not assigned to a variable or used in a condition).
    # Pattern: line is like "    FDateTime::ParseIso8601(..." without if/=.
    if grep -qP '^\s*FDateTime::ParseIso8601\s*\(' "$file"; then
        fail "CHECK 3 – ParseIso8601 return ignored" \
            "File: $file" \
            "FDateTime::ParseIso8601() return value is not checked (call result discarded)." \
            "Fix: use 'if (!FDateTime::ParseIso8601(..., Out)) { /* handle error */ }'"
        grep -nP '^\s*FDateTime::ParseIso8601\s*\(' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 3 done"
echo

# =============================================================================
# CHECK 4: BIO_write / BIO_read return value checked for < 0
#
# OpenSSL BIO functions return -1 on error, not 0.  An equality check
# "Written != BytesRead" catches it numerically but the error branch should
# explicitly test for negative values first to avoid misleading log output.
# =============================================================================
echo "--- CHECK 4: BIO_write/BIO_read return values handled correctly ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bBIO_write\b|\bBIO_read\b' "$file"; then
        # Warn if no "< 0" or "<0" check is present alongside BIO calls.
        if ! grep -qP '<\s*0' "$file"; then
            fail "CHECK 4 – BIO_write/BIO_read negative return" \
                "File: $file" \
                "Uses BIO_write or BIO_read but has no '< 0' error check." \
                "Fix: check 'if (Written < 0)' before '!= BytesRead' comparison."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 4 done"
echo

# =============================================================================
# CHECK 5: REST API POST/PATCH/DELETE handlers have CheckBodySize
#
# Every HTTP handler lambda that reads the request body via BodyToString()
# must call BanJson::CheckBodySize(Req) first to return HTTP 413 rather
# than silently treating an oversized body as empty JSON.
# =============================================================================
echo "--- CHECK 5: CheckBodySize present in all body-reading REST handlers ---"

while IFS= read -r -d '' file; do
    if grep -qP 'BodyToString' "$file"; then
        body_count=$(grep -cP 'BodyToString' "$file")
        check_count=$(grep -cP 'CheckBodySize' "$file")
        # Each BodyToString site should have a corresponding CheckBodySize.
        # We use a simple count heuristic; if counts differ, flag for review.
        if [[ "$check_count" -lt "$body_count" ]]; then
            fail "CHECK 5 – CheckBodySize coverage" \
                "File: $file" \
                "BodyToString() called $body_count time(s) but CheckBodySize() only $check_count time(s)." \
                "Fix: add 'if (auto SizeErr = BanJson::CheckBodySize(Req)) { Done(MoveTemp(SizeErr)); return true; }' before each BodyToString call."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 5 done"
echo

# =============================================================================
# CHECK 6: FCriticalSection / FScopeLock present in all registry classes
#          that have shared mutable state and are accessed from multiple threads
#
# Only flag classes whose names end in "Registry" or "Database" or "Log" —
# these are the subsystems that are explicitly designed to be thread-safe
# (they already use FScopeLock in their implementations).
# UObjects like BanEnforcer, BanDiscordSubsystem etc. are game-thread-only
# and intentionally do not use mutexes; they are excluded from this check.
# =============================================================================
echo "--- CHECK 6: FCriticalSection present in thread-safe registry/database headers ---"

while IFS= read -r -d '' file; do
    # Only scan headers whose filename matches the thread-safe registry pattern.
    basename="$(basename "$file" .h)"
    if [[ "$basename" =~ Registry$|Database$|Log$ ]]; then
        has_container=$(grep -cP '\bTMap\b|\bTArray\b|\bTSet\b' "$file")
        has_mutex=$(grep -cP '\bFCriticalSection\b|\bFRWLock\b' "$file")
        if [[ "$has_container" -gt 0 && "$has_mutex" -eq 0 ]]; then
            fail "CHECK 6 – missing FCriticalSection" \
                "File: $file" \
                "Registry/Database/Log class declares TMap/TArray/TSet but has no FCriticalSection or FRWLock." \
                "Fix: add 'mutable FCriticalSection Mutex;' and use FScopeLock in every public method."
        fi
    fi
done < <(list_header_files)

pass "CHECK 6 done"
echo

# =============================================================================
# CHECK 7: Double-fragment size check before MoveTemp (WebSocket server)
#
# In SMLWebSocketServerRunnable.cpp the oversized-fragment check must appear
# BEFORE the MoveTemp(Payload) that consumes the data.  If the check comes
# after MoveTemp, the payload is already destroyed when we try to reject it.
# =============================================================================
echo "--- CHECK 7: Fragment size check before MoveTemp in WebSocket server ---"

SERVER_RUNNABLE="$MOD_ROOT/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp"
if [[ -f "$SERVER_RUNNABLE" ]]; then
    # Get line numbers for the size check and the MoveTemp.
    size_line=$(grep -n 'MaxMessageBytes\|MaxFrameSize\|too large\|oversized\|MaxPayload' "$SERVER_RUNNABLE" | head -1 | cut -d: -f1)
    move_line=$(grep -n 'MoveTemp.*Payload\|FragmentBuffer.*MoveTemp' "$SERVER_RUNNABLE" | head -1 | cut -d: -f1)
    if [[ -n "$size_line" && -n "$move_line" ]]; then
        if [[ "$size_line" -gt "$move_line" ]]; then
            fail "CHECK 7 – size check after MoveTemp" \
                "File: $SERVER_RUNNABLE" \
                "Size check (line $size_line) comes AFTER MoveTemp (line $move_line)." \
                "Fix: move the size check above the MoveTemp(Payload) call."
        fi
    fi
fi

pass "CHECK 7 done"
echo

# =============================================================================
# CHECK 8: static_cast<int32> from float/double without range guard
#
# Casting an unbounded float/double to int32 is UB when the value is outside
# [INT32_MIN, INT32_MAX].  Every static_cast<int32>() applied to a float or
# the result of a floating-point function (GetIniFloat, etc.) must be wrapped
# in a clamping helper or explicit range check.
# =============================================================================
echo "--- CHECK 8: static_cast<int32> from float/double without range guard ---"

while IFS= read -r -d '' file; do
    # Look for direct static_cast<int32>(GetIniFloat or similar float source).
    if grep -qP 'static_cast<int32>\s*\(\s*(GetIniFloat|GetFloat|\.GetFloat|[0-9]+\.[0-9]+f?)' "$file"; then
        fail "CHECK 8 – unsafe float-to-int32 cast" \
            "File: $file" \
            "static_cast<int32> applied to a float/GetIniFloat result without range guard." \
            "Fix: use a helper like GetIniInt() that clamps before casting."
        grep -nP 'static_cast<int32>\s*\(\s*(GetIniFloat|GetFloat|\.GetFloat)' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 8 done"
echo

# =============================================================================
# CHECK 9: Integer overflow in duration arithmetic (ban/mute parsing)
#
# Duration parsers that do "Total += Num * Multiplier" (or similar literal
# multipliers like 10080/1440/60) can overflow int64 when user input is very
# large.  Each multiplication must be preceded by an INT64_MAX / Multiplier
# guard AND the digit-accumulation loop must also guard against overflow.
#
# We detect the pattern by looking for unguarded "Num * 10080" style literals
# without a corresponding INT64_MAX guard present anywhere in the same file.
# BanChatCommands.cpp was fixed with explicit per-multiplier guards; we verify
# all other duration parsers are equally protected.
# =============================================================================
echo "--- CHECK 9: Overflow guards in duration arithmetic ---"

while IFS= read -r -d '' file; do
    # Check for the literal multiplier pattern (week/day/hour in minutes).
    if grep -qP 'Num\s*\*\s*(10080|1440|3600|86400)\b' "$file"; then
        # The file must have at least one INT64_MAX guard for the multiplication.
        if ! grep -qP 'INT64_MAX\s*/\s*(Multiplier|multiplier|10080|1440|3600|86400)' "$file"; then
            fail "CHECK 9 – duration multiplication overflow" \
                "File: $file" \
                "Has 'Num * <week/day/hour multiplier>' without INT64_MAX / Multiplier overflow guard." \
                "Fix: add 'if (Multiplier > 1 && Num > INT64_MAX / Multiplier) return 0/−1;' before each multiply."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 9 done"
echo

# =============================================================================
# CHECK 10: JSON parse root validated before use
#
# Every FJsonSerializer::Deserialize call must check both the bool return AND
# Root.IsValid() before accessing Root->...  A missing check leads to a null
# dereference when JSON input is malformed.
# =============================================================================
echo "--- CHECK 10: JSON parse results validated before use ---"

while IFS= read -r -d '' file; do
    # Count Deserialize calls vs. IsValid() checks in the same file.
    deser_count=$(grep -cP 'FJsonSerializer::Deserialize' "$file")
    valid_count=$(grep -cP '\.IsValid\(\)' "$file")
    if [[ "$deser_count" -gt 0 && "$valid_count" -lt "$deser_count" ]]; then
        fail "CHECK 10 – JSON parse not fully validated" \
            "File: $file" \
            "FJsonSerializer::Deserialize called $deser_count time(s) but IsValid() only $valid_count time(s)." \
            "Fix: every Deserialize call site must check '|| !Root.IsValid()'."
    fi
done < <(list_cpp_files)

pass "CHECK 10 done"
echo

# =============================================================================
# CHECK 11: FCString::Atoi (int32) without a Len <= guard
#
# FCString::Atoi silently overflows when the string is longer than 10 digits
# (INT32_MAX has 10 digits).  Every file that calls FCString::Atoi — as
# opposed to FCString::Atoi64 — must also have at least one ".Len() <="
# check to reject strings that are too long before converting them.
#
# Note: FCString::Atoi64 has its own separate check (CHECK 13).
# =============================================================================
echo "--- CHECK 11: FCString::Atoi (int32) guarded by Len() <= check ---"

while IFS= read -r -d '' file; do
    # Does this file have a real (non-comment) FCString::Atoi call (not Atoi64)?
    # Pipeline: grep all Atoi lines, then discard pure-comment lines.
    atoi_lines=$(grep -P '\bFCString::Atoi\b(?!64)' "$file" | grep -vP '^\s*//')
    if [[ -n "$atoi_lines" ]]; then
        # Accept either .Len() or ->Len() paired with any comparison operator (<, >, <=, >=).
        if ! grep -qP '(?:\.|->)Len\(\)\s*[<>!]' "$file"; then
            fail "CHECK 11 – FCString::Atoi without Len() guard" \
                "File: $file" \
                "Calls FCString::Atoi (int32) but has no Len() length-guard." \
                "Fix: add 'if (!Str.IsNumeric() || Str.Len() > 10 || (Str.Len() == 10 && Str > TEXT(\"2147483647\"))) return Default;' before each Atoi call."
            echo "$atoi_lines" | while IFS= read -r ln; do
                echo "       Line: $ln"
            done
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 11 done"
echo

# =============================================================================
# CHECK 12: FCString::Atof result guarded with FMath::IsFinite
#
# FCString::Atof can return NaN or ±Infinity for inputs like "nan", "inf",
# or extremely large exponents.  Every file that calls FCString::Atof must
# also call FMath::IsFinite on the result before using it, to prevent NaN
# or Inf from propagating into configuration values, ban durations, or
# arithmetic expressions.
# =============================================================================
echo "--- CHECK 12: FCString::Atof result guarded with FMath::IsFinite ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bFCString::Atof\b' "$file"; then
        if ! grep -qP '\bFMath::IsFinite\b' "$file"; then
            fail "CHECK 12 – FCString::Atof without FMath::IsFinite guard" \
                "File: $file" \
                "Calls FCString::Atof but has no FMath::IsFinite guard on the result." \
                "Fix: add 'return FMath::IsFinite(Result) ? Result : Default;' after each Atof call."
            grep -nP '\bFCString::Atof\b' "$file" | while IFS= read -r ln; do
                echo "       Line: $ln"
            done
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 12 done"
echo

# =============================================================================
# CHECK 13: FCString::Atoi64 (int64) without IsNumeric() and Len() <= guard
#
# FCString::Atoi64 overflows for strings exceeding INT64_MAX (19 digits).
# Every file that calls FCString::Atoi64 must have BOTH:
#   1. An IsNumeric() check — to reject non-digit strings.
#   2. A Len() <= check  — to reject strings longer than 19 characters.
# The lexicographic overflow guard (comparing to "9223372036854775807") is
# encouraged but not required by this check; the two guards above are the
# minimum mandatory protection.
# =============================================================================
echo "--- CHECK 13: FCString::Atoi64 guarded by IsNumeric() and Len() <= ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bFCString::Atoi64\b' "$file"; then
        # Accept either .IsNumeric() or FChar::IsDigit as a character-validity guard.
        has_isnumeric=$(grep -cP '\.IsNumeric\(\)|FChar::IsDigit' "$file")
        # Accept .Len() or ->Len() followed by any comparison operator (<, >, <=, >=, ==, !=).
        has_len=$(grep -cP '(?:\.|->)Len\(\)\s*[<>!]' "$file")
        if [[ "$has_isnumeric" -eq 0 || "$has_len" -eq 0 ]]; then
            fail "CHECK 13 – FCString::Atoi64 without full safety guard" \
                "File: $file" \
                "Calls FCString::Atoi64 but is missing IsNumeric()/IsDigit guard (count=$has_isnumeric) or Len() comparison guard (count=$has_len)." \
                "Fix: add 'if (!Str.IsNumeric() || Str.Len() > 19 || (Str.Len() == 19 && Str > TEXT(\"9223372036854775807\"))) return Default;' before each Atoi64 call."
            grep -nP '\bFCString::Atoi64\b' "$file" | while IFS= read -r ln; do
                echo "       Line: $ln"
            done
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 13 done"
echo

# =============================================================================
# CHECK 14: AsyncTask lambdas must capture UObjects via TWeakObjectPtr
#
# Lambdas passed to AsyncTask run on a background thread and may execute
# after the owning UObject has been garbage-collected.  Capturing a raw
# UObject pointer (e.g. "this" or a member pointer) in such a lambda is a
# use-after-free.  Every file that uses AsyncTask must also use the
# TWeakObjectPtr (or WeakThis / WeakOwner) capture pattern to guard against
# accessing a destroyed object.
# =============================================================================
echo "--- CHECK 14: AsyncTask lambdas capture UObjects via TWeakObjectPtr ---"

while IFS= read -r -d '' file; do
    if grep -qP '\bAsyncTask\b' "$file"; then
        if ! grep -qP '\bTWeakObjectPtr\b|\bWeakThis\b|\bWeakOwner\b|\bWeakGI\b' "$file"; then
            fail "CHECK 14 – AsyncTask without TWeakObjectPtr capture" \
                "File: $file" \
                "Uses AsyncTask but has no TWeakObjectPtr/WeakThis guard for captured UObjects." \
                "Fix: capture UObject* as 'TWeakObjectPtr<T> WeakX = this;' and check '.IsValid()' before use inside the lambda."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 14 done"
echo

# =============================================================================
# CHECK 15: PathParams uid values must be URL-decoded before use
#
# UE's HTTP server does NOT automatically URL-decode path parameter values.
# A UID like "EOS:abc%3Axyz" will arrive with the '%3A' still encoded.
# Every file that reads a uid path parameter via PathParams.FindRef("uid")
# must also call FGenericPlatformHttp::UrlDecode() on the raw value before
# passing it to database lookups or string comparisons.
# =============================================================================
echo "--- CHECK 15: PathParams uid values URL-decoded before use ---"

while IFS= read -r -d '' file; do
    if grep -qP 'PathParams.*\buid\b' "$file"; then
        if ! grep -qP '\bUrlDecode\b' "$file"; then
            fail "CHECK 15 – PathParams uid not URL-decoded" \
                "File: $file" \
                "Reads uid from PathParams but has no UrlDecode() call." \
                "Fix: add 'const FString Uid = FGenericPlatformHttp::UrlDecode(RawUid);' after PathParams.FindRef(\"uid\")."
        fi
    fi
done < <(list_cpp_files)

pass "CHECK 15 done"
echo

# =============================================================================
# CHECK 16: Signed numeric validation must not allow '-' in non-leading positions
#
# Pattern to reject:
#   if (!FChar::IsDigit(Ch) && Ch != TEXT('-')) { ... }
# This accepts malformed values like "12-3", which then reach FCString::Atoi64
# and can be misparsed.  Signed integer validators must only allow an optional
# single leading '-' and require all remaining characters to be digits.
# =============================================================================
echo "--- CHECK 16: Signed numeric validation rejects interior '-' characters ---"

while IFS= read -r -d '' file; do
    if grep -qP '!\s*FChar::IsDigit\([^)]*\)\s*&&\s*[^;]*!=\s*TEXT\((?:\x27-\x27|\x22-\x22)\)' "$file"; then
        fail "CHECK 16 – permissive signed-number validator" \
            "File: $file" \
            "Uses '!FChar::IsDigit(...) && ... != TEXT('-')' style validation, which allows '-' in non-leading positions." \
            "Fix: validate as optional leading '-' only, then require digits for every remaining character."
        grep -nP '!\s*FChar::IsDigit\([^)]*\)\s*&&\s*[^;]*!=\s*TEXT\((?:\x27-\x27|\x22-\x22)\)' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 16 done"
echo

# =============================================================================
# CHECK 17: EscapeMarkdown applied to Uid in all Discord embed Field() calls
#
# Every user-controlled string in a Discord embed must go through EscapeMarkdown
# before being placed in a Field() call.  The Uid (compound UID) is user-
# controlled (includes "IP:" prefixes with caller-supplied values) and must be
# escaped just like PlayerName, Reason, etc.
# =============================================================================
echo "--- CHECK 17: EscapeMarkdown applied to Uid in Discord embed Field() calls ---"

while IFS= read -r -d '' file; do
    # Look for Field(...Uid...) patterns where EscapeMarkdown is absent
    if grep -qP 'Field\s*\(\s*TEXT\s*\(\s*"UID"\s*\)\s*,\s*(?!EscapeMarkdown)[A-Za-z]' "$file"; then
        fail "CHECK 17 – raw Uid in Discord embed Field()" \
            "File: $file" \
            "A Field(TEXT(\"UID\"), ...) call passes a raw string without EscapeMarkdown()." \
            "Fix: wrap the value with EscapeMarkdown(...)."
        grep -nP 'Field\s*\(\s*TEXT\s*\(\s*"UID"\s*\)\s*,\s*(?!EscapeMarkdown)[A-Za-z]' "$file" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
done < <(list_cpp_files)

pass "CHECK 17 done"
echo

# =============================================================================
# CHECK 18: EAppealStatus::Dismissed is declared in BanTypes.h
#
# The codebase uses EAppealStatus::Dismissed in multiple call sites.  If the
# enum value is not declared the project will not compile.
# =============================================================================
echo "--- CHECK 18: EAppealStatus::Dismissed declared in BanTypes.h ---"

BANTYPES_H="$(find "$REPO_ROOT" -name BanTypes.h -path '*/BanSystem/*' | head -1)"
if [[ -z "$BANTYPES_H" ]]; then
    fail "CHECK 18 – BanTypes.h not found" \
        "Expected file: Mods/BanSystem/Source/BanSystem/Public/BanTypes.h" \
        "BanTypes.h could not be located in the repository."
elif ! grep -q 'Dismissed' "$BANTYPES_H"; then
    fail "CHECK 18 – EAppealStatus::Dismissed missing from BanTypes.h" \
        "File: $BANTYPES_H" \
        "EAppealStatus::Dismissed is used across the codebase but is not declared in the enum." \
        "Fix: add 'Dismissed UMETA(DisplayName = \"Dismissed\"),' to EAppealStatus."
fi

pass "CHECK 18 done"
echo

# =============================================================================
# CHECK 19: AppealToJson() must handle EAppealStatus::Dismissed
#
# AppealToJson() serializes FBanAppealEntry to JSON for every REST endpoint
# that returns appeal records.  If the Dismissed case is absent from the
# switch the status is silently serialized as "pending", misleading API
# consumers and any downstream tooling.
# =============================================================================
echo "--- CHECK 19: AppealToJson() handles EAppealStatus::Dismissed ---"

RESTAPI_CPP="$(find "$REPO_ROOT" -name BanRestApi.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$RESTAPI_CPP" ]]; then
    fail "CHECK 19 – BanRestApi.cpp not found" \
        "Expected file: Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp"
else
    # Check for 'case EAppealStatus::Dismissed: StatusStr = TEXT("dismissed");' in AppealToJson
    if ! grep -qP 'case\s+EAppealStatus::Dismissed\s*:\s*StatusStr\s*=\s*TEXT\s*\(\s*"dismissed"\s*\)' "$RESTAPI_CPP"; then
        fail "CHECK 19 – AppealToJson() missing Dismissed→\"dismissed\" mapping" \
            "File: $RESTAPI_CPP" \
            "AppealToJson() does not map EAppealStatus::Dismissed to the JSON string \"dismissed\"." \
            "Fix: add 'case EAppealStatus::Dismissed: StatusStr = TEXT(\"dismissed\"); break;' to the switch."
    fi
fi

pass "CHECK 19 done"
echo

# =============================================================================
# CHECK 20: GET /appeals status filter must recognise "dismissed"
#
# The ?status= query-parameter filter in the GET /appeals REST handler must
# map the string "dismissed" to EAppealStatus::Dismissed.  Without this,
# ?status=dismissed silently returns Pending appeals instead.
# =============================================================================
echo "--- CHECK 20: GET /appeals status filter maps \"dismissed\" ---"

if [[ -z "$RESTAPI_CPP" ]]; then
    fail "CHECK 20 – BanRestApi.cpp not found" \
        "Expected file: Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp"
else
    # Check for 'else if (Norm == TEXT("dismissed")) FilterStatus = EAppealStatus::Dismissed;'
    if ! grep -qP 'Norm\s*==\s*TEXT\s*\(\s*"dismissed"\s*\)\s*\)\s*FilterStatus\s*=\s*EAppealStatus::Dismissed' "$RESTAPI_CPP"; then
        fail "CHECK 20 – GET /appeals filter missing \"dismissed\" mapping" \
            "File: $RESTAPI_CPP" \
            "The ?status= filter does not handle \"dismissed\", so ?status=dismissed returns wrong results." \
            "Fix: add 'else if (Norm == TEXT(\"dismissed\")) FilterStatus = EAppealStatus::Dismissed;' to the filter."
    fi
fi

pass "CHECK 20 done"
echo

# =============================================================================
# CHECK 21: /history command uses W.Id (persistent warning ID) not i+1
#
# The /history chat command must display the persistent database primary key
# (W.Id, an int64) as the warning number, not a transient loop counter.
# Using i+1 produces fake numbers that do not match the IDs required by
# /clearwarn, causing player confusion and inability to clear specific warnings.
# =============================================================================
echo "--- CHECK 21: /history command uses W.Id, not loop counter i+1 ---"

BANCHATCHMDS_CPP="$(find "$REPO_ROOT" -name BanChatCommands.cpp -path '*/BanChatCommands/*' | head -1)"
if [[ -z "$BANCHATCHMDS_CPP" ]]; then
    fail "CHECK 21 – BanChatCommands.cpp not found" \
        "Expected file: Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp"
else
    # The /history loop must not use "i + 1" with %d as the displayed warning number in a Printf
    if grep -qP 'FString::Printf\s*\(\s*TEXT\s*\([^)]*#%d[^)]*\)[^,]*,\s*i\s*\+\s*1\s*,' "$BANCHATCHMDS_CPP"; then
        fail "CHECK 21 – /history displays loop counter i+1 instead of W.Id" \
            "File: $BANCHATCHMDS_CPP" \
            "The warning display loop uses 'i + 1' as the displayed ID, not the persistent W.Id." \
            "Fix: replace '#%d ... i + 1' with '#%lld ... W.Id'."
        grep -nP 'FString::Printf\s*\(\s*TEXT\s*\([^)]*#%d[^)]*\)[^,]*,\s*i\s*\+\s*1\s*,' "$BANCHATCHMDS_CPP" | while IFS= read -r ln; do
            echo "       Line: $ln"
        done
    fi
fi

pass "CHECK 21 done"
echo

# =============================================================================
# CHECK 22: RemoveBanByUid/RemoveBanById rolls back in-memory removal on save failure
# =============================================================================
echo "--- CHECK 22: BanDatabase rolls back Bans entry on SaveToFile failure ---"
BANDB_CPP="$(find "$REPO_ROOT" -name BanDatabase.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$BANDB_CPP" ]]; then
    fail "CHECK 22 – BanDatabase.cpp not found"
else
    # The rollback inserts the captured OutEntry back via Bans.Add(OutEntry).
    if ! grep -qP 'Bans\.Add\s*\(\s*OutEntry\s*\)' "$BANDB_CPP"; then
        fail "CHECK 22 – RemoveBanByUid/RemoveBanById does not roll back Bans on SaveToFile failure" \
            "File: $BANDB_CPP" \
            "When SaveToFile fails after Bans.RemoveAll, the entry must be re-inserted: Bans.Add(OutEntry)."
    fi
fi
pass "CHECK 22 done"
echo

# =============================================================================
# CHECK 23: AddBan/AddBanSkipIfPermanentExists rolls back in-memory addition on save failure
# =============================================================================
echo "--- CHECK 23: BanDatabase rolls back Bans entry on AddBan SaveToFile failure ---"
if [[ -z "$BANDB_CPP" ]]; then
    fail "CHECK 23 – BanDatabase.cpp not found"
else
    # The rollback removes the ghost entry via Bans.RemoveAll([&NewEntry]...).
    if ! grep -qP 'Bans\.RemoveAll\s*\(\s*\[&NewEntry\]' "$BANDB_CPP"; then
        fail "CHECK 23 – AddBan/AddBanSkipIfPermanentExists does not roll back Bans on SaveToFile failure" \
            "File: $BANDB_CPP" \
            "When SaveToFile fails after Bans.Add(NewEntry), the entry must be removed: Bans.RemoveAll([&NewEntry]...)."
    fi
fi
pass "CHECK 23 done"
echo

# =============================================================================
# CHECK 24: RestApiRemoveCounterpartBans fires NotifyBanRemoved for each counterpart
# =============================================================================
echo "--- CHECK 24: RestApiRemoveCounterpartBans fires NotifyBanRemoved per counterpart ---"
BANREST_CPP="$(find "$REPO_ROOT" -name BanRestApi.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$BANREST_CPP" ]]; then
    fail "CHECK 24 – BanRestApi.cpp not found"
else
    # Verify NotifyBanRemoved is called with LinkedUid inside RestApiRemoveCounterpartBans.
    if ! grep -qP 'NotifyBanRemoved\s*\(\s*LinkedUid' "$BANREST_CPP"; then
        fail "CHECK 24 – RestApiRemoveCounterpartBans does not call NotifyBanRemoved for linked counterparts" \
            "File: $BANREST_CPP" \
            "Each successful RemoveBanByUid in RestApiRemoveCounterpartBans must be followed by NotifyBanRemoved."
    fi
fi
pass "CHECK 24 done"
echo

# =============================================================================
# CHECK 25: MuteRegistry::GetRegistryPath() respects UBanSystemConfig::DatabasePath
# =============================================================================
echo "--- CHECK 25: MuteRegistry::GetRegistryPath() respects DatabasePath ---"
MUTEREG_CPP="$(find "$REPO_ROOT" -name MuteRegistry.cpp -path '*/BanChatCommands/*' | head -1)"
if [[ -z "$MUTEREG_CPP" ]]; then
    fail "CHECK 25 – MuteRegistry.cpp not found"
else
    # The fix reads Cfg->DatabasePath inside GetRegistryPath.
    if ! grep -qP 'Cfg\s*->\s*DatabasePath' "$MUTEREG_CPP"; then
        fail "CHECK 25 – MuteRegistry::GetRegistryPath() is hardcoded; it ignores UBanSystemConfig::DatabasePath" \
            "File: $MUTEREG_CPP" \
            "GetRegistryPath() must read Cfg->DatabasePath like other registries."
    fi
fi
pass "CHECK 25 done"
echo

# =============================================================================
# CHECK 26: PlayerNoteRegistry::GetRegistryPath() respects UBanSystemConfig::DatabasePath
# =============================================================================
echo "--- CHECK 26: PlayerNoteRegistry::GetRegistryPath() respects DatabasePath ---"
NOTEREG_CPP="$(find "$REPO_ROOT" -name PlayerNoteRegistry.cpp -path '*/BanChatCommands/*' | head -1)"
if [[ -z "$NOTEREG_CPP" ]]; then
    fail "CHECK 26 – PlayerNoteRegistry.cpp not found"
else
    if ! grep -qP 'Cfg\s*->\s*DatabasePath' "$NOTEREG_CPP"; then
        fail "CHECK 26 – PlayerNoteRegistry::GetRegistryPath() is hardcoded; it ignores UBanSystemConfig::DatabasePath" \
            "File: $NOTEREG_CPP" \
            "GetRegistryPath() must read Cfg->DatabasePath like other registries."
    fi
fi
pass "CHECK 26 done"
echo

# =============================================================================
# CHECK 27: AddWarning(FWarningEntry) only stamps WarnDate when caller left it default
# =============================================================================
echo "--- CHECK 27: AddWarning(FWarningEntry) preserves caller-supplied WarnDate ---"
WARNREG_CPP="$(find "$REPO_ROOT" -name PlayerWarningRegistry.cpp -path '*/BanSystem/*' | head -1)"
if [[ -z "$WARNREG_CPP" ]]; then
    fail "CHECK 27 – PlayerWarningRegistry.cpp not found"
else
    # The fix guards the WarnDate stamp with: if (Entry.WarnDate == FDateTime(0))
    if ! grep -qP 'WarnDate\s*==\s*FDateTime\s*\(\s*0\s*\)' "$WARNREG_CPP"; then
        fail "CHECK 27 – AddWarning(FWarningEntry) unconditionally overwrites caller's WarnDate" \
            "File: $WARNREG_CPP" \
            "The struct overload must only set WarnDate = UtcNow() when Entry.WarnDate == FDateTime(0)."
    fi
fi
pass "CHECK 27 done"
echo

# =============================================================================
# CHECK 28: wl_approve button does not grant access when WhitelistCommandRoleId is empty
# =============================================================================
echo "--- CHECK 28: wl_approve button bHasRole not initialised from empty role ---"
DBS_CPP="$(find "$REPO_ROOT" -name DiscordBridgeSubsystem.cpp -path '*/DiscordBridge/*' | head -1)"
if [[ -z "$DBS_CPP" ]]; then
    fail "CHECK 28 – DiscordBridgeSubsystem.cpp not found"
else
    # Negative: old vulnerable pattern must be absent.
    if grep -qP 'bHasRole\s*=\s*WhitelistConfig\.WhitelistCommandRoleId\.IsEmpty\(\)' "$DBS_CPP"; then
        fail "CHECK 28 – wl_approve handler sets bHasRole=true when WhitelistCommandRoleId is empty" \
            "File: $DBS_CPP" \
            "Change 'bHasRole = WhitelistConfig.WhitelistCommandRoleId.IsEmpty()' to 'bHasRole = false'."
    fi
fi
pass "CHECK 28 done"
echo

# =============================================================================
# CHECK 29: GET /notes serialises actual note entries (not just count)
# =============================================================================
echo "--- CHECK 29: GET /notes serialises note entries via reflection ---"
if [[ -z "$BANREST_CPP" ]]; then
    fail "CHECK 29 – BanRestApi.cpp not found"
else
    # Verify the handler uses FScriptArrayHelper to iterate entries and
    # FStructProperty to access the inner struct.
    if ! grep -qP 'CastField\s*<\s*FStructProperty\s*>\s*\(\s*NotesProp\s*->\s*Inner\s*\)' "$BANREST_CPP"; then
        fail "CHECK 29 – GET /notes always returns an empty notes array" \
            "File: $BANREST_CPP" \
            "The handler must iterate NotesProp entries via FScriptArrayHelper and read fields via CastField<FStructProperty>(NotesProp->Inner)."
    fi
fi
pass "CHECK 29 done"
echo

# =============================================================================
# CHECK 30: Loader paths reject non-positive persisted IDs
# =============================================================================
echo "--- CHECK 30: persisted IDs are validated as > 0 on load ---"
AUDITLOG_CPP="$(find "$REPO_ROOT" -name BanAuditLog.cpp -path '*/BanSystem/*' | head -1)"
WARNREG_CPP_CHECK30="$(find "$REPO_ROOT" -name PlayerWarningRegistry.cpp -path '*/BanSystem/*' | head -1)"
SCHEDREG_CPP="$(find "$REPO_ROOT" -name ScheduledBanRegistry.cpp -path '*/BanSystem/*' | head -1)"
BANDB_CPP_CHECK30="$(find "$REPO_ROOT" -name BanDatabase.cpp -path '*/BanSystem/*' | head -1)"
TICKETSUB_CPP="$(find "$REPO_ROOT" -name TicketSubsystem.cpp -path '*/DiscordBridge/*' | head -1)"

if [[ -z "$AUDITLOG_CPP" ]]; then
    fail "CHECK 30 – BanAuditLog.cpp not found"
elif ! grep -qP 'Entry\.Id\s*<=\s*0' "$AUDITLOG_CPP"; then
    fail "CHECK 30 – BanAuditLog accepts non-positive entry IDs from disk" \
        "File: $AUDITLOG_CPP" \
        "LoadFromFile() should skip entries when Entry.Id <= 0."
fi

if [[ -z "$WARNREG_CPP_CHECK30" ]]; then
    fail "CHECK 30 – PlayerWarningRegistry.cpp not found"
elif ! grep -qP 'Entry\.Id\s*<=\s*0' "$WARNREG_CPP_CHECK30"; then
    fail "CHECK 30 – PlayerWarningRegistry accepts non-positive warning IDs from disk" \
        "File: $WARNREG_CPP_CHECK30" \
        "LoadFromFile() should skip warnings when Entry.Id <= 0."
fi

if [[ -z "$SCHEDREG_CPP" ]]; then
    fail "CHECK 30 – ScheduledBanRegistry.cpp not found"
elif ! grep -qP 'Entry\.Id\s*<=\s*0' "$SCHEDREG_CPP"; then
    fail "CHECK 30 – ScheduledBanRegistry accepts non-positive scheduled-ban IDs from disk" \
        "File: $SCHEDREG_CPP" \
        "LoadFromFile() should skip entries when Entry.Id <= 0."
fi

if [[ -z "$BANDB_CPP_CHECK30" ]]; then
    fail "CHECK 30 – BanDatabase.cpp not found"
elif ! grep -qP 'OutEntry\.Id\s*>\s*0' "$BANDB_CPP_CHECK30"; then
    fail "CHECK 30 – BanDatabase::JsonToEntry does not require positive IDs" \
        "File: $BANDB_CPP_CHECK30" \
        "JsonToEntry() should reject entries unless OutEntry.Id > 0."
fi

if [[ -z "$TICKETSUB_CPP" ]]; then
    fail "CHECK 30 – TicketSubsystem.cpp not found"
elif ! grep -qP 'ParsedAppealId\s*>\s*0' "$TICKETSUB_CPP"; then
    fail "CHECK 30 – TicketSubsystem restores non-positive appeal IDs from ticket state" \
        "File: $TICKETSUB_CPP" \
        "State restore should add OpenerToAppealId only when ParsedAppealId > 0."
fi

pass "CHECK 30 done"
echo

# =============================================================================
# CHECK 31: GET /notes serialises note IDs as string, not double
#
# int64 IDs cast to double lose precision for values > 2^53.  The fix is to use
# SetStringField(TEXT("id"), FString::Printf(TEXT("%lld"), IdVal)) matching the
# convention used for all other IDs in the REST API.
# =============================================================================
echo "--- CHECK 31: GET /notes serialises note IDs as decimal string not double ---"

BANRESTAPI_CPP_CHECK31="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$BANRESTAPI_CPP_CHECK31" ]]; then
    fail "CHECK 31 – BanRestApi.cpp not found"
elif grep -qP 'SetNumberField\s*\(\s*TEXT\s*\(\s*"id"\s*\)' "$BANRESTAPI_CPP_CHECK31"; then
    fail "CHECK 31 – GET /notes serialises note ID as double (precision loss for id > 2^53)" \
        "File: $BANRESTAPI_CPP_CHECK31" \
        "Use SetStringField(TEXT(\"id\"), FString::Printf(TEXT(\"%lld\"), IdVal)) instead."
fi

pass "CHECK 31 done"
echo

# =============================================================================
# CHECK 32: BanSyncClient skips NotifyBanCreated for peer ban updates
#
# When a peer sync message updates an existing ban (bWasUpdate=true), firing
# NotifyBanCreated posts a spurious "🔨 Player Banned" webhook for what was
# merely a reason/duration edit.  The guard "if (!bWasUpdate)" must be present.
# =============================================================================
echo "--- CHECK 32: BanSyncClient skips NotifyBanCreated for peer ban updates ---"

BANSYNC_CPP_CHECK32="$(list_cpp_files | tr '\0' '\n' | grep 'BanSyncClient\.cpp' | head -1)"

if [[ -z "$BANSYNC_CPP_CHECK32" ]]; then
    fail "CHECK 32 – BanSyncClient.cpp not found"
elif ! grep -qP 'bWasUpdate' "$BANSYNC_CPP_CHECK32"; then
    fail "CHECK 32 – BanSyncClient does not track bWasUpdate for peer ban updates" \
        "File: $BANSYNC_CPP_CHECK32" \
        "Set bWasUpdate=true when RemoveBanByUid is called before re-adding and guard" \
        "NotifyBanCreated with 'if (!bWasUpdate)'."
elif ! grep -qP '!\s*bWasUpdate' "$BANSYNC_CPP_CHECK32"; then
    fail "CHECK 32 – BanSyncClient does not guard NotifyBanCreated with !bWasUpdate" \
        "File: $BANSYNC_CPP_CHECK32" \
        "NotifyBanCreated must be skipped when bWasUpdate is true."
fi

pass "CHECK 32 done"
echo

# =============================================================================
# CHECK 33: RemoveExpiredEntries clears the output array before appending
#
# Without OutExpiredNames.Reset() at the top, callers that reuse the array
# across multiple calls silently accumulate stale entries.
# =============================================================================
echo "--- CHECK 33: RemoveExpiredEntries clears output array before appending ---"

WLMGR_CPP_CHECK33="$(list_cpp_files | tr '\0' '\n' | grep 'WhitelistManager\.cpp' | head -1)"

if [[ -z "$WLMGR_CPP_CHECK33" ]]; then
    fail "CHECK 33 – WhitelistManager.cpp not found"
elif ! grep -qP 'OutExpiredNames\s*\.\s*(Reset|Empty)\s*\(' "$WLMGR_CPP_CHECK33"; then
    fail "CHECK 33 – RemoveExpiredEntries does not clear OutExpiredNames before appending" \
        "File: $WLMGR_CPP_CHECK33" \
        "Add OutExpiredNames.Reset() at the start of RemoveExpiredEntries."
fi

pass "CHECK 33 done"
echo

# =============================================================================
# CHECK 34: whitelist list / GetAll() / GetAllEntries() display code filters expired
#
# The whitelist list and groups commands call GetAllEntries() and must skip entries
# where ExpiresAt is set and <= UtcNow().  The GetAll() helper also must filter.
# =============================================================================
echo "--- CHECK 34: whitelist list/groups display filters expired entries ---"

WLMGR_CPP_CHECK34="$WLMGR_CPP_CHECK33"
DSUB_CPP_CHECK34="$(list_cpp_files | tr '\0' '\n' | grep 'DiscordBridgeSubsystem\.cpp' | head -1)"

if [[ -z "$WLMGR_CPP_CHECK34" ]]; then
    fail "CHECK 34 – WhitelistManager.cpp not found"
elif ! grep -qP 'ExpiresAt\s*<=\s*Now\w*' "$WLMGR_CPP_CHECK34"; then
    fail "CHECK 34 – GetAll() in WhitelistManager.cpp does not filter expired entries" \
        "File: $WLMGR_CPP_CHECK34" \
        "Skip entries where ExpiresAt.GetTicks() > 0 && ExpiresAt <= Now in GetAll()."
fi

if [[ -z "$DSUB_CPP_CHECK34" ]]; then
    fail "CHECK 34 – DiscordBridgeSubsystem.cpp not found"
elif ! grep -qP 'ExpiresAt\s*<=\s*Now\w*' "$DSUB_CPP_CHECK34"; then
    fail "CHECK 34 – whitelist list/groups in DiscordBridgeSubsystem.cpp do not filter expired entries" \
        "File: $DSUB_CPP_CHECK34" \
        "In 'whitelist list' and 'whitelist groups' skip entries where ExpiresAt <= Now."
fi

pass "CHECK 34 done"
echo

# =============================================================================
# CHECK 35: BanAppealRegistry rolls back + suppresses broadcasts on save failure
#
# AddAppeal/AddAppealIfNoDuplicate must remove in-memory inserts and restore NextId
# when SaveToFile fails. Review/Delete paths must also roll back in-memory changes
# so disk and memory do not diverge.
# =============================================================================
echo "--- CHECK 35: BanAppealRegistry save-failure rollback keeps memory/disk in sync ---"

APPEALREG_CPP_CHECK35="$(list_cpp_files | tr '\0' '\n' | grep 'BanAppealRegistry\.cpp' | head -1)"

if [[ -z "$APPEALREG_CPP_CHECK35" ]]; then
    fail "CHECK 35 - BanAppealRegistry.cpp not found"
elif ! grep -qP 'const\s+int64\s+OriginalNextId\s*=\s*NextId' "$APPEALREG_CPP_CHECK35"; then
    fail "CHECK 35 - AddAppeal paths do not snapshot NextId before insert" \
        "File: $APPEALREG_CPP_CHECK35" \
        "AddAppeal/AddAppealIfNoDuplicate should capture OriginalNextId before incrementing."
elif ! grep -qP 'Appeals\.RemoveAt\s*\(\s*Appeals\.Num\s*\(\s*\)\s*-\s*1\s*\)' "$APPEALREG_CPP_CHECK35"; then
    fail "CHECK 35 - AddAppeal paths do not roll back in-memory insert on save failure" \
        "File: $APPEALREG_CPP_CHECK35" \
        "On SaveToFile failure, remove the just-added appeal from Appeals."
elif ! grep -qP 'NextId\s*=\s*OriginalNextId' "$APPEALREG_CPP_CHECK35"; then
    fail "CHECK 35 - AddAppeal paths do not restore NextId on save failure" \
        "File: $APPEALREG_CPP_CHECK35" \
        "On SaveToFile failure, restore NextId to OriginalNextId."
elif ! grep -qP 'Appeals\.Insert\s*\(\s*RemovedEntry\s*,\s*RemoveIdx\s*\)' "$APPEALREG_CPP_CHECK35"; then
    fail "CHECK 35 - DeleteAppeal does not restore removed entry when save fails" \
        "File: $APPEALREG_CPP_CHECK35" \
        "DeleteAppeal should reinsert RemovedEntry at RemoveIdx if SaveToFile fails."
elif ! grep -qP 'A\s*=\s*PrevEntry' "$APPEALREG_CPP_CHECK35"; then
    fail "CHECK 35 - ReviewAppeal does not restore previous entry when save fails" \
        "File: $APPEALREG_CPP_CHECK35" \
        "ReviewAppeal should restore A from PrevEntry if SaveToFile fails."
fi

pass "CHECK 35 done"
echo

# =============================================================================
# CHECK 36: Add/Log operations roll back in-memory state when save fails
#
# Persist-first semantics: when SaveToFile() fails, in-memory mutation must be
# undone so memory and disk stay consistent.
# =============================================================================
echo "--- CHECK 36: add/log save-failure rollback restores in-memory state ---"

NOTEREG_CPP_CHECK36="$(list_cpp_files | tr '\0' '\n' | grep 'PlayerNoteRegistry\.cpp' | head -1)"
WARNREG_CPP_CHECK36="$(list_cpp_files | tr '\0' '\n' | grep 'PlayerWarningRegistry\.cpp' | head -1)"
SCHEDREG_CPP_CHECK36="$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"
AUDITLOG_CPP_CHECK36="$(list_cpp_files | tr '\0' '\n' | grep 'BanAuditLog\.cpp' | head -1)"

if [[ -z "$NOTEREG_CPP_CHECK36" ]]; then
    fail "CHECK 36 – PlayerNoteRegistry.cpp not found"
elif ! grep -qP 'OriginalNextId' "$NOTEREG_CPP_CHECK36" \
     || ! grep -qP 'Notes\.RemoveAt\s*\(\s*Notes\.Num\s*\(\s*\)\s*-\s*1\s*\)' "$NOTEREG_CPP_CHECK36" \
     || ! grep -qP 'NextId\s*=\s*OriginalNextId' "$NOTEREG_CPP_CHECK36"; then
    fail "CHECK 36 – PlayerNoteRegistry AddNote does not roll back insert + NextId on save failure" \
        "File: $NOTEREG_CPP_CHECK36"
fi

if [[ -z "$WARNREG_CPP_CHECK36" ]]; then
    fail "CHECK 36 – PlayerWarningRegistry.cpp not found"
elif ! grep -qP 'OriginalNextId' "$WARNREG_CPP_CHECK36" \
     || ! grep -qP 'Warnings\.RemoveAt\s*\(\s*Warnings\.Num\s*\(\s*\)\s*-\s*1\s*\)' "$WARNREG_CPP_CHECK36" \
     || ! grep -qP 'NextId\s*=\s*OriginalNextId' "$WARNREG_CPP_CHECK36"; then
    fail "CHECK 36 – PlayerWarningRegistry AddWarning paths do not roll back insert + NextId on save failure" \
        "File: $WARNREG_CPP_CHECK36"
fi

if [[ -z "$SCHEDREG_CPP_CHECK36" ]]; then
    fail "CHECK 36 – ScheduledBanRegistry.cpp not found"
elif ! grep -qP 'OriginalNextId' "$SCHEDREG_CPP_CHECK36" \
     || ! grep -qP 'Pending\.RemoveAt\s*\(\s*Pending\.Num\s*\(\s*\)\s*-\s*1\s*\)' "$SCHEDREG_CPP_CHECK36" \
     || ! grep -qP 'NextId\s*=\s*OriginalNextId' "$SCHEDREG_CPP_CHECK36"; then
    fail "CHECK 36 – ScheduledBanRegistry AddScheduled does not roll back insert + NextId on save failure" \
        "File: $SCHEDREG_CPP_CHECK36"
fi

if [[ -z "$AUDITLOG_CPP_CHECK36" ]]; then
    fail "CHECK 36 – BanAuditLog.cpp not found"
elif ! grep -qP 'NextId\s*=\s*OriginalNextId' "$AUDITLOG_CPP_CHECK36"; then
    fail "CHECK 36 – BanAuditLog::LogAction does not roll back NextId on save failure" \
        "File: $AUDITLOG_CPP_CHECK36"
elif ! grep -qP 'Entries\.RemoveAt\s*\(\s*Entries\.Num\s*\(\s*\)\s*-\s*1\s*\)' "$AUDITLOG_CPP_CHECK36"; then
    fail "CHECK 36 – BanAuditLog::LogAction does not roll back memory and NextId on save failure" \
        "File: $AUDITLOG_CPP_CHECK36"
fi

pass "CHECK 36 done"
echo

# =============================================================================
# CHECK 37: Delete operations reinsert removed entry on save failure
# =============================================================================
echo "--- CHECK 37: delete save-failure rollback restores removed entries ---"

NOTEREG_CPP_CHECK37="$NOTEREG_CPP_CHECK36"
WARNREG_CPP_CHECK37="$WARNREG_CPP_CHECK36"
SCHEDREG_CPP_CHECK37="$SCHEDREG_CPP_CHECK36"

if [[ -z "$NOTEREG_CPP_CHECK37" ]]; then
    fail "CHECK 37 – PlayerNoteRegistry.cpp not found"
elif ! grep -qP 'Notes\.Insert\s*\(\s*RemovedEntry\s*,\s*RemoveIdx\s*\)' "$NOTEREG_CPP_CHECK37"; then
    fail "CHECK 37 – PlayerNoteRegistry::DeleteNote does not restore removed entry on save failure" \
        "File: $NOTEREG_CPP_CHECK37"
fi

if [[ -z "$WARNREG_CPP_CHECK37" ]]; then
    fail "CHECK 37 – PlayerWarningRegistry.cpp not found"
elif ! grep -qP 'Warnings\.Insert\s*\(\s*RemovedEntry\s*,\s*RemovedIdx\s*\)' "$WARNREG_CPP_CHECK37"; then
    fail "CHECK 37 – PlayerWarningRegistry::DeleteWarningById does not restore removed entry on save failure" \
        "File: $WARNREG_CPP_CHECK37"
fi

if [[ -z "$SCHEDREG_CPP_CHECK37" ]]; then
    fail "CHECK 37 – ScheduledBanRegistry.cpp not found"
elif ! grep -qP 'Pending\.Insert\s*\(\s*RemovedEntry\s*,\s*RemoveIdx\s*\)' "$SCHEDREG_CPP_CHECK37"; then
    fail "CHECK 37 – ScheduledBanRegistry::DeleteScheduled does not restore removed entry on save failure" \
        "File: $SCHEDREG_CPP_CHECK37"
fi

pass "CHECK 37 done"
echo

# =============================================================================
# CHECK 38: MuteRegistry save-failure rollback and broadcast suppression
# =============================================================================
echo "--- CHECK 38: MuteRegistry save-failure rollback keeps state + events consistent ---"

MUTEREG_CPP_CHECK38="$(list_cpp_files | tr '\0' '\n' | grep 'MuteRegistry\.cpp' | head -1)"

if [[ -z "$MUTEREG_CPP_CHECK38" ]]; then
    fail "CHECK 38 – MuteRegistry.cpp not found"
elif ! grep -qP 'bPersisted' "$MUTEREG_CPP_CHECK38" \
     || ! grep -qP 'OnPlayerMuted\.Broadcast' "$MUTEREG_CPP_CHECK38" \
     || ! grep -qP 'Expired\.Reset\s*\(' "$MUTEREG_CPP_CHECK38"; then
    fail "CHECK 38 – MuteRegistry does not fully roll back in-memory changes and suppress events on save failure" \
        "File: $MUTEREG_CPP_CHECK38"
elif ! grep -qP 'Mutes\.RemoveAt\s*\(\s*Mutes\.Num\s*\(\s*\)\s*-\s*1\s*\)|Mutes\.Add\s*\(\s*(Prev|Removed)Entry\s*\)' "$MUTEREG_CPP_CHECK38"; then
    fail "CHECK 38 – MuteRegistry does not roll back Mutes array on save failure" \
        "File: $MUTEREG_CPP_CHECK38"
fi

pass "CHECK 38 done"
echo

# =============================================================================
# CHECK 39: PlayerSessionRegistry save-failure rollback + event gating
# =============================================================================
echo "--- CHECK 39: PlayerSessionRegistry rollback and event gating on save failure ---"

SESSIONREG_CPP_CHECK39="$(list_cpp_files | tr '\0' '\n' | grep 'PlayerSessionRegistry\.cpp' | head -1)"

if [[ -z "$SESSIONREG_CPP_CHECK39" ]]; then
    fail "CHECK 39 – PlayerSessionRegistry.cpp not found"
elif ! grep -qP 'const\s+FPlayerSessionRecord\s+PrevRecord\s*=\s*R' "$SESSIONREG_CPP_CHECK39" \
     || ! grep -qP 'R\s*=\s*PrevRecord' "$SESSIONREG_CPP_CHECK39" \
     || ! grep -qP 'Records\.RemoveAt\s*\(\s*Records\.Num\s*\(\s*\)\s*-\s*1\s*\)' "$SESSIONREG_CPP_CHECK39" \
     || ! grep -qP 'const\s+TArray<FPlayerSessionRecord>\s+PrevRecords\s*=\s*Records' "$SESSIONREG_CPP_CHECK39" \
     || ! grep -qP 'Records\s*=\s*PrevRecords' "$SESSIONREG_CPP_CHECK39" \
     || ! grep -qP 'if\s*\(\s*bPersisted\s*\)' "$SESSIONREG_CPP_CHECK39" \
     || ! grep -qP 'PushEvent\s*\(\s*TEXT\("player_join"\)' "$SESSIONREG_CPP_CHECK39"; then
    fail "CHECK 39 – PlayerSessionRegistry does not fully roll back in-memory edits and gate player_join event on save success" \
        "File: $SESSIONREG_CPP_CHECK39"
fi

pass "CHECK 39 done"
echo


# =============================================================================
# CHECK 40: PruneExpiredBans rolls back in-memory removal and clears Expired
#           on SaveToFile failure (BUG-4)
# =============================================================================
echo "--- CHECK 40: PruneExpiredBans rolls back on save failure and suppresses spurious events ---"

BANDB_CPP_CHECK40="$(list_cpp_files | tr '\0' '\n' | grep 'BanDatabase\.cpp' | head -1)"

if [[ -z "$BANDB_CPP_CHECK40" ]]; then
    fail "CHECK 40 – BanDatabase.cpp not found"
elif ! grep -qP 'Bans\.Append\s*\(\s*Expired\s*\)' "$BANDB_CPP_CHECK40" \
     || ! grep -qP 'Expired\.Reset\s*\(' "$BANDB_CPP_CHECK40"; then
    fail "CHECK 40 – PruneExpiredBans does not roll back Bans and clear Expired on SaveToFile failure" \
        "File: $BANDB_CPP_CHECK40"
fi

pass "CHECK 40 done"
echo

# =============================================================================
# CHECK 41: POST /bans temp-ban uses 3-arg AddBanSkipIfPermanentExists (BUG-1)
# =============================================================================
echo "--- CHECK 41: POST /bans temp-ban uses 3-arg AddBanSkipIfPermanentExists ---"

RESTAPI_CPP_CHECK41="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$RESTAPI_CPP_CHECK41" ]]; then
    fail "CHECK 41 – BanRestApi.cpp not found"
elif ! grep -qP 'AddBanSkipIfPermanentExists\s*\(\s*Entry\s*,\s*&Saved\s*,\s*&bSkippedPerm\s*\)' "$RESTAPI_CPP_CHECK41"; then
    fail "CHECK 41 – POST /bans temp-ban does not use 3-arg AddBanSkipIfPermanentExists" \
        "File: $RESTAPI_CPP_CHECK41"
fi

pass "CHECK 41 done"
echo

# =============================================================================
# CHECK 42: PATCH /bans/:uid rejects negative durationMinutes (BUG-2)
# =============================================================================
echo "--- CHECK 42: PATCH /bans/:uid rejects negative durationMinutes values ---"

RESTAPI_CPP_CHECK42="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$RESTAPI_CPP_CHECK42" ]]; then
    fail "CHECK 42 – BanRestApi.cpp not found"
elif ! grep -qP 'bHasDuration\s*&&\s*\(!FMath::IsFinite\(DurationMinutesDbl\)\s*\|\|\s*DurationMinutesDbl\s*<\s*0\.0\)' "$RESTAPI_CPP_CHECK42"; then
    fail "CHECK 42 – PATCH /bans/:uid does not reject non-finite/negative durationMinutes" \
        "File: $RESTAPI_CPP_CHECK42" \
        "Fix: reject !FMath::IsFinite(DurationMinutesDbl) || DurationMinutesDbl < 0.0."
fi

pass "CHECK 42 done"
echo

# =============================================================================
# CHECK 43: BanSyncClient updates existing peer bans without silent-unban window
# =============================================================================
echo "--- CHECK 43: BanSyncClient updates existing peer bans in place ---"

SYNCCLIENT_CPP_CHECK43="$(list_cpp_files | tr '\0' '\n' | grep 'BanSyncClient\.cpp' | head -1)"

if [[ -z "$SYNCCLIENT_CPP_CHECK43" ]]; then
    fail "CHECK 43 – BanSyncClient.cpp not found"
else
    if ! grep -qP 'DB->UpdateBan\s*\(' "$SYNCCLIENT_CPP_CHECK43"; then
        fail "CHECK 43 – BanSyncClient does not use UpdateBan for peer edits" \
            "File: $SYNCCLIENT_CPP_CHECK43"
    fi
    if ! grep -qP 'if\s*\(\s*bWasUpdate\s*\)' "$SYNCCLIENT_CPP_CHECK43"; then
        fail "CHECK 43 – BanSyncClient does not early-return after a successful in-place update" \
            "File: $SYNCCLIENT_CPP_CHECK43"
    fi
    if ! perl -0777 -ne 'exit 0 if /FBanEntry\s+StillExisting\s*;\s*if\s*\(\s*DB->IsCurrentlyBanned\(Uid,\s*StillExisting\)\s*\)\s*return;/s; exit 1' "$SYNCCLIENT_CPP_CHECK43"; then
        fail "CHECK 43 – BanSyncClient still has a peer-update silent-unban window" \
            "File: $SYNCCLIENT_CPP_CHECK43"
    fi
fi

pass "CHECK 43 done"
echo

# =============================================================================
# CHECK 44: POST /bans/ip returns 409 Conflict (not 200) when permanent ban exists
# =============================================================================
echo "--- CHECK 44: POST /bans/ip returns 409 Conflict on permanent-ban skip ---"

RESTAPI_CPP_CHECK44="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$RESTAPI_CPP_CHECK44" ]]; then
    fail "CHECK 44 – BanRestApi.cpp not found"
else
    # There must NOT be any path that sets Code=Ok immediately after a bSkippedPerm check in the IP ban block.
    # More precisely: after the bIpBanAdded / bSkippedPerm block, the response must use Conflict.
    if ! grep -qP 'bSkippedPerm.*\n.*Conflict|Resp->Code\s*=\s*EHttpServerResponseCodes::Conflict' "$RESTAPI_CPP_CHECK44"; then
        # Try a two-line grep via pcregrep or perl
        if ! perl -0777 -ne 'exit 0 if /bSkippedPerm[^}]*EHttpServerResponseCodes::Conflict/s; exit 1' "$RESTAPI_CPP_CHECK44"; then
            fail "CHECK 44 – POST /bans/ip does not return 409 Conflict on permanent-ban skip" \
                "File: $RESTAPI_CPP_CHECK44"
        fi
    fi
fi

pass "CHECK 44 done"
echo

# =============================================================================
# CHECK 45: POST /warnings auto-ban escalation uses OutSaved (not 2-arg) so id != 0
# =============================================================================
echo "--- CHECK 45: POST /warnings auto-ban escalation uses 3-arg AddBanSkipIfPermanentExists ---"

RESTAPI_CPP_CHECK45="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$RESTAPI_CPP_CHECK45" ]]; then
    fail "CHECK 45 – BanRestApi.cpp not found"
elif ! perl -0777 -ne 'exit 0 if /SavedAutoban.*\n.*AddBanSkipIfPermanentExists\s*\(\s*AutoBan\s*,\s*&SavedAutoban/s; exit 1' "$RESTAPI_CPP_CHECK45"; then
    fail "CHECK 45 – POST /warnings auto-ban does not use 3-arg AddBanSkipIfPermanentExists with OutSaved" \
        "File: $RESTAPI_CPP_CHECK45"
fi

pass "CHECK 45 done"
echo

# =============================================================================
# CHECK 46: DoBan (BanChatCommands) uses OutSaved so NotifyBanCreated carries correct Id
# =============================================================================
echo "--- CHECK 46: BanChatCommands DoBan uses OutSaved for NotifyBanCreated ---"

BANCHCMD_CPP_CHECK46="$(list_cpp_files | tr '\0' '\n' | grep 'BanChatCommands\.cpp' | head -1)"

if [[ -z "$BANCHCMD_CPP_CHECK46" ]]; then
    fail "CHECK 46 – BanChatCommands.cpp not found"
elif ! grep -qP 'AddBan\s*\(\s*Entry\s*,\s*&Saved\s*\)' "$BANCHCMD_CPP_CHECK46"; then
    fail "CHECK 46 – DoBan does not use AddBan with OutSaved" \
        "File: $BANCHCMD_CPP_CHECK46"
fi

pass "CHECK 46 done"
echo

# =============================================================================
# CHECK 47: HandleWarnCommand auto-ban uses OutSaved so NotifyBanCreated carries correct Id
# =============================================================================
echo "--- CHECK 47: BanChatCommands HandleWarnCommand auto-ban uses OutSaved ---"

BANCHCMD_CPP_CHECK47="$(list_cpp_files | tr '\0' '\n' | grep 'BanChatCommands\.cpp' | head -1)"

if [[ -z "$BANCHCMD_CPP_CHECK47" ]]; then
    fail "CHECK 47 – BanChatCommands.cpp not found"
elif ! grep -qP 'AddBanSkipIfPermanentExists\s*\(\s*AutoBanEntry\s*,\s*&SavedAutoban\s*,\s*&bSkipped\s*\)' "$BANCHCMD_CPP_CHECK47"; then
    fail "CHECK 47 – HandleWarnCommand auto-ban does not use 3-arg AddBanSkipIfPermanentExists with OutSaved" \
        "File: $BANCHCMD_CPP_CHECK47"
fi

pass "CHECK 47 done"
echo

# =============================================================================
# CHECK 48: HandleQbanCommand uses OutSaved so NotifyBanCreated carries correct Id
# =============================================================================
echo "--- CHECK 48: BanChatCommands HandleQbanCommand uses OutSaved for NotifyBanCreated ---"

BANCHCMD_CPP_CHECK48="$(list_cpp_files | tr '\0' '\n' | grep 'BanChatCommands\.cpp' | head -1)"

if [[ -z "$BANCHCMD_CPP_CHECK48" ]]; then
    fail "CHECK 48 – BanChatCommands.cpp not found"
elif ! grep -qP 'AddBan\s*\(\s*Ban\s*,\s*&QBanSaved\s*\)' "$BANCHCMD_CPP_CHECK48"; then
    fail "CHECK 48 – HandleQbanCommand does not use AddBan with OutSaved" \
        "File: $BANCHCMD_CPP_CHECK48"
fi

pass "CHECK 48 done"
echo

# =============================================================================
# CHECK 49: Bulk-ban path uses OutSaved so NotifyBanCreated carries correct Id
# =============================================================================
echo "--- CHECK 49: BanChatCommands bulk-ban uses OutSaved for NotifyBanCreated ---"

BANCHCMD_CPP_CHECK49="$(list_cpp_files | tr '\0' '\n' | grep 'BanChatCommands\.cpp' | head -1)"

if [[ -z "$BANCHCMD_CPP_CHECK49" ]]; then
    fail "CHECK 49 – BanChatCommands.cpp not found"
elif ! grep -qP 'AddBan\s*\(\s*Ban\s*,\s*&BulkBanSaved\s*\)' "$BANCHCMD_CPP_CHECK49"; then
    fail "CHECK 49 – Bulk-ban does not use AddBan with OutSaved" \
        "File: $BANCHCMD_CPP_CHECK49"
fi

pass "CHECK 49 done"
echo

# =============================================================================
# CHECK 50: PlayerNoteRegistry uses static_cast<double>(INT64_MAX) for nextId guard
# =============================================================================
echo "--- CHECK 50: PlayerNoteRegistry uses INT64_MAX (not magic 9.2e18) for nextId guard ---"

NOTEREG_CPP_CHECK50="$(list_cpp_files | tr '\0' '\n' | grep 'PlayerNoteRegistry\.cpp' | head -1)"

if [[ -z "$NOTEREG_CPP_CHECK50" ]]; then
    fail "CHECK 50 – PlayerNoteRegistry.cpp not found"
elif grep -qP '9\.2e18' "$NOTEREG_CPP_CHECK50"; then
    fail "CHECK 50 – PlayerNoteRegistry still uses magic 9.2e18 instead of static_cast<double>(INT64_MAX)" \
        "File: $NOTEREG_CPP_CHECK50"
fi

pass "CHECK 50 done"
echo

# =============================================================================
# CHECK 51: MuteRegistry writes null expireDate for indefinite mutes
# =============================================================================
echo "--- CHECK 51: MuteRegistry writes null expireDate for indefinite mutes ---"

MUTEREG_CPP_CHECK51="$(list_cpp_files | tr '\0' '\n' | grep 'MuteRegistry\.cpp' | head -1)"

if [[ -z "$MUTEREG_CPP_CHECK51" ]]; then
    fail "CHECK 51 – MuteRegistry.cpp not found"
elif ! grep -qP 'bIsIndefinite.*FJsonValueNull|FJsonValueNull.*bIsIndefinite' "$MUTEREG_CPP_CHECK51"; then
    # Check via perl for multi-line
    if ! perl -0777 -ne 'exit 0 if /bIsIndefinite.*\n.*FJsonValueNull/s; exit 1' "$MUTEREG_CPP_CHECK51"; then
        fail "CHECK 51 – MuteRegistry does not write null expireDate for indefinite mutes" \
            "File: $MUTEREG_CPP_CHECK51"
    fi
fi

pass "CHECK 51 done"
echo

# =============================================================================
# CHECK 52: WhitelistManager uses TryGetArrayField instead of GetArrayField
# =============================================================================
echo "--- CHECK 52: WhitelistManager uses TryGetArrayField (not GetArrayField) ---"

WHITELIST_CPP_CHECK52="$(list_cpp_files | tr '\0' '\n' | grep 'WhitelistManager\.cpp' | head -1)"

if [[ -z "$WHITELIST_CPP_CHECK52" ]]; then
    fail "CHECK 52 – WhitelistManager.cpp not found"
elif perl -ne 'exit 0 if /->GetArrayField\s*\(/; END { exit 1 }' "$WHITELIST_CPP_CHECK52"; then
    fail "CHECK 52 – WhitelistManager still uses GetArrayField instead of TryGetArrayField" \
        "File: $WHITELIST_CPP_CHECK52"
fi

pass "CHECK 52 done"
echo

# =============================================================================
# CHECK 53: Ban-created notifications fire after counterpart bans are added
# =============================================================================
echo "--- CHECK 53: counterpart-ban linking occurs before NotifyBanCreated in ban-create flows ---"

BANCHCMD_CPP_CHECK53="$(list_cpp_files | tr '\0' '\n' | grep 'BanChatCommands\.cpp' | head -1)"
BANREST_CPP_CHECK53="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
BANDISCORD_CPP_CHECK53="$(list_cpp_files | tr '\0' '\n' | grep 'BanDiscordSubsystem\.cpp' | head -1)"

if [[ -z "$BANCHCMD_CPP_CHECK53" || -z "$BANREST_CPP_CHECK53" || -z "$BANDISCORD_CPP_CHECK53" ]]; then
    fail "CHECK 53 – required source file(s) not found" \
        "BanChatCommands: ${BANCHCMD_CPP_CHECK53:-missing}" \
        "BanRestApi: ${BANREST_CPP_CHECK53:-missing}" \
        "BanDiscordSubsystem: ${BANDISCORD_CPP_CHECK53:-missing}"
else
    if perl -0777 -ne 'exit 0 if /NotifyBanCreated\s*\(\s*BulkBanSaved\s*\)\s*;\s*(?:\/\/[^\n]*\n\s*)*BanChat::AddCounterpartBans\s*\(\s*this\s*,\s*Sender\s*,\s*Uid\s*,\s*RawUid/s; exit 1' "$BANCHCMD_CPP_CHECK53"; then
        fail "CHECK 53 – BanChatCommands bulk-ban still notifies before AddCounterpartBans" \
            "File: $BANCHCMD_CPP_CHECK53"
    fi

    if perl -0777 -ne 'exit 0 if /NotifyBanCreated\s*\(\s*(?:Saved|AddedEntry)\s*\)\s*;\s*(?:\/\/[^\n]*\n\s*)*RestApiAddCounterpartBans\s*\(/s; exit 1' "$BANREST_CPP_CHECK53"; then
        fail "CHECK 53 – BanRestApi still notifies before RestApiAddCounterpartBans in a create path" \
            "File: $BANREST_CPP_CHECK53"
    fi

    if perl -0777 -ne 'exit 0 if /NotifyBanCreated\s*\(\s*(?:Entry|Ban)\s*\)\s*;\s*(?:\/\/[^\n]*\n\s*)*BanDiscordHelpers::AddCounterpartBans\s*\(\s*this\s*,\s*DB\s*,\s*Uid/s; exit 1' "$BANDISCORD_CPP_CHECK53"; then
        fail "CHECK 53 – BanDiscordSubsystem still notifies before AddCounterpartBans in a direct ban flow" \
            "File: $BANDISCORD_CPP_CHECK53"
    fi
fi

pass "CHECK 53 done"
echo


# =============================================================================
# CHECK 54: UpdateBan snapshots entry before mutating (rollback on save failure)
# =============================================================================
echo "--- CHECK 54: UpdateBan snapshots entry before mutating ---"

BANDB_CPP_CHECK54="$(list_cpp_files | tr '\0' '\n' | grep 'BanDatabase\.cpp' | head -1)"

if [[ -z "$BANDB_CPP_CHECK54" ]]; then
    fail "CHECK 54 – BanDatabase.cpp not found"
else
    # Snapshot must appear between "if (!Found) return false;" and "Mutator(*Found)"
    if ! perl -0777 -ne 'exit 0 if /if\s*\(!Found\)\s*return false;\s*(?:\/\/[^\n]*\n\s*)*const FBanEntry Snapshot\s*=\s*\*Found;/s; exit 1' "$BANDB_CPP_CHECK54"; then
        fail "CHECK 54 – UpdateBan does not snapshot *Found before calling Mutator" \
            "File: $BANDB_CPP_CHECK54"
    fi
    # Rollback: *Found = Snapshot on save failure
    if ! perl -0777 -ne 'exit 0 if /UpdateBan.*?if\s*\(!bSaved\).*?\*Found\s*=\s*Snapshot/s; exit 1' "$BANDB_CPP_CHECK54"; then
        fail "CHECK 54 – UpdateBan does not restore *Found = Snapshot on SaveToFile failure" \
            "File: $BANDB_CPP_CHECK54"
    fi
fi

pass "CHECK 54 done"
echo

# =============================================================================
# CHECK 55: AddBan/AddBanSkipIfPermanentExists upsert restores old entry on rollback
# =============================================================================
echo "--- CHECK 55: AddBan upsert restores old entry on save failure ---"

BANDB_CPP_CHECK55="$BANDB_CPP_CHECK54"

if [[ -z "$BANDB_CPP_CHECK55" ]]; then
    fail "CHECK 55 – BanDatabase.cpp not found"
else
    # AddBan must call GetBanByUid_Locked before the upsert RemoveAll
    if ! perl -0777 -ne 'exit 0 if /GetBanByUid_Locked\s*\(\s*Entry\.Uid\s*,\s*OldEntry\s*\).*?Bans\.RemoveAll.*?Entry\.Uid.*?bHadOldEntry.*?Bans\.Add\s*\(\s*OldEntry\s*\)/s; exit 1' "$BANDB_CPP_CHECK55"; then
        fail "CHECK 55 – AddBan does not restore old entry on upsert rollback" \
            "File: $BANDB_CPP_CHECK55"
    fi
fi

pass "CHECK 55 done"
echo

# =============================================================================
# CHECK 56: UnlinkBans rolls back LinkedUids on SaveToFile failure
# =============================================================================
echo "--- CHECK 56: UnlinkBans rolls back on SaveToFile failure ---"

BANDB_CPP_CHECK56="$BANDB_CPP_CHECK54"

if [[ -z "$BANDB_CPP_CHECK56" ]]; then
    fail "CHECK 56 – BanDatabase.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /UnlinkBans.*?LinkSnapshots.*?bDirty\s*&&\s*!bSaved.*?E\.LinkedUids\s*=\s*\*OldLinks/s; exit 1' "$BANDB_CPP_CHECK56"; then
        fail "CHECK 56 – UnlinkBans does not roll back LinkedUids on SaveToFile failure" \
            "File: $BANDB_CPP_CHECK56"
    fi
fi

pass "CHECK 56 done"
echo

# =============================================================================
# CHECK 57: POST /bans/bulk temp-ban uses 3-arg AddBanSkipIfPermanentExists
# =============================================================================
echo "--- CHECK 57: POST /bans/bulk temp-ban uses 3-arg AddBanSkipIfPermanentExists ---"

BANREST_CPP_CHECK57="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$BANREST_CPP_CHECK57" ]]; then
    fail "CHECK 57 – BanRestApi.cpp not found"
else
    # 3-arg form: AddBanSkipIfPermanentExists(Ban, &Saved, &bBatchSkipped)
    if grep -qP 'AddBanSkipIfPermanentExists\s*\(\s*Ban\s*,\s*bBatchSkipped\s*\)' "$BANREST_CPP_CHECK57"; then
        fail "CHECK 57 – POST /bans/bulk still uses 2-arg AddBanSkipIfPermanentExists (no &Saved)" \
            "File: $BANREST_CPP_CHECK57"
    fi
    if ! grep -qP 'AddBanSkipIfPermanentExists\s*\(\s*Ban\s*,\s*&Saved\s*,\s*&bBatchSkipped\s*\)' "$BANREST_CPP_CHECK57"; then
        fail "CHECK 57 – POST /bans/bulk does not use 3-arg AddBanSkipIfPermanentExists(&Saved)" \
            "File: $BANREST_CPP_CHECK57"
    fi
fi

pass "CHECK 57 done"
echo

# =============================================================================
# CHECK 58: Rate-limit response uses HTTP 429 (not 400)
# =============================================================================
echo "--- CHECK 58: appeal rate-limit response uses HTTP 429 ---"

BANREST_CPP_CHECK58="$BANREST_CPP_CHECK57"

if [[ -z "$BANREST_CPP_CHECK58" ]]; then
    fail "CHECK 58 – BanRestApi.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /Too many appeal submissions.*TooManyRequests/s; exit 1' "$BANREST_CPP_CHECK58"; then
        fail "CHECK 58 – appeal rate-limit still responds with 400 instead of 429" \
            "File: $BANREST_CPP_CHECK58"
    fi
fi

pass "CHECK 58 done"
echo

# =============================================================================
# CHECK 59: WarningToJson includes hasExpiry and expireDate
# =============================================================================
echo "--- CHECK 59: WarningToJson serialises hasExpiry / expireDate ---"

BANREST_CPP_CHECK59="$BANREST_CPP_CHECK57"

if [[ -z "$BANREST_CPP_CHECK59" ]]; then
    fail "CHECK 59 – BanRestApi.cpp not found"
else
    if ! grep -qP 'SetBoolField.*hasExpiry' "$BANREST_CPP_CHECK59"; then
        fail "CHECK 59 – WarningToJson missing SetBoolField(\"hasExpiry\",...)" \
            "File: $BANREST_CPP_CHECK59"
    fi
    if ! grep -qP 'SetStringField.*expireDate.*ExpireDate\.ToIso8601\(\)' "$BANREST_CPP_CHECK59"; then
        fail "CHECK 59 – WarningToJson missing expireDate field" \
            "File: $BANREST_CPP_CHECK59"
    fi
fi

pass "CHECK 59 done"
echo

# =============================================================================
# CHECK 60: ScheduledToJson includes retryCount
# =============================================================================
echo "--- CHECK 60: ScheduledToJson serialises retryCount ---"

BANREST_CPP_CHECK60="$BANREST_CPP_CHECK57"

if [[ -z "$BANREST_CPP_CHECK60" ]]; then
    fail "CHECK 60 – BanRestApi.cpp not found"
else
    if ! grep -qP 'SetNumberField.*retryCount.*RetryCount' "$BANREST_CPP_CHECK60"; then
        fail "CHECK 60 – ScheduledToJson missing retryCount field" \
            "File: $BANREST_CPP_CHECK60"
    fi
fi

pass "CHECK 60 done"
echo

# =============================================================================
# CHECK 61: WhitelistManager Save_Locked returns bool + AddPlayer/RemovePlayer rollback
# =============================================================================
echo "--- CHECK 61: WhitelistManager Save_Locked returns bool; AddPlayer/RemovePlayer rollback ---"

WM_CPP_CHECK61="$(list_cpp_files | tr '\0' '\n' | grep 'WhitelistManager\.cpp' | head -1)"
WM_H_CHECK61="$(find "$MOD_ROOT" -name 'WhitelistManager.h' | head -1)"

if [[ -z "$WM_CPP_CHECK61" || -z "$WM_H_CHECK61" ]]; then
    fail "CHECK 61 – WhitelistManager source file(s) not found"
else
    if ! grep -qP 'bool\s+FWhitelistManager::Save_Locked' "$WM_CPP_CHECK61"; then
        fail "CHECK 61 – WhitelistManager::Save_Locked does not return bool" \
            "File: $WM_CPP_CHECK61"
    fi
    # AddPlayer must call Save_Locked and rollback on failure
    if ! perl -0777 -ne 'exit 0 if /AddPlayer.*?if\s*\(!Save_Locked\(\)\).*?Entries\.RemoveAt/s; exit 1' "$WM_CPP_CHECK61"; then
        fail "CHECK 61 – WhitelistManager::AddPlayer has no rollback on Save_Locked failure" \
            "File: $WM_CPP_CHECK61"
    fi
    # RemovePlayer must rollback
    if ! perl -0777 -ne 'exit 0 if /RemovePlayer.*?if\s*\(!Save_Locked\(\)\).*?Entries\.Insert/s; exit 1' "$WM_CPP_CHECK61"; then
        fail "CHECK 61 – WhitelistManager::RemovePlayer has no rollback on Save_Locked failure" \
            "File: $WM_CPP_CHECK61"
    fi
fi

pass "CHECK 61 done"
echo

# =============================================================================
# CHECK 62: HandleBanNameCommand returns early on DB write failure (no kick-without-ban)
# =============================================================================
echo "--- CHECK 62: HandleBanNameCommand returns early on EOS DB write failure ---"

BANDIS_CPP_CHECK62="$(list_cpp_files | tr '\0' '\n' | grep 'BanDiscordSubsystem\.cpp' | head -1)"

if [[ -z "$BANDIS_CPP_CHECK62" ]]; then
    fail "CHECK 62 – BanDiscordSubsystem.cpp not found"
else
    # Must have an else branch (DB failure) that calls Respond and returns before kick
    if ! perl -0777 -ne 'exit 0 if /AddBanSkipIfPermanentExists\s*\(\s*EosEntry\s*,\s*bEosSkipped\s*\).*?else\s*\{[^}]*Failed to write ban[^}]*return/s; exit 1' "$BANDIS_CPP_CHECK62"; then
        fail "CHECK 62 – HandleBanNameCommand does not return early on EOS DB write failure" \
            "File: $BANDIS_CPP_CHECK62"
    fi
fi

pass "CHECK 62 done"
echo

# =============================================================================
# CHECK 63: HandleExtendBanCommand lambda re-checks bIsPermanent under lock
# =============================================================================
echo "--- CHECK 63: HandleExtendBanCommand lambda re-checks bIsPermanent under lock ---"

BANDIS_CPP_CHECK63="$BANDIS_CPP_CHECK62"

if [[ -z "$BANDIS_CPP_CHECK63" ]]; then
    fail "CHECK 63 – BanDiscordSubsystem.cpp not found"
else
    if ! grep -qP 'if\s*\(\s*E\.bIsPermanent\s*\)\s*return;' "$BANDIS_CPP_CHECK63"; then
        fail "CHECK 63 – HandleExtendBanCommand lambda does not re-check E.bIsPermanent under lock" \
            "File: $BANDIS_CPP_CHECK63"
    fi
fi

pass "CHECK 63 done"
echo

# =============================================================================
# CHECK 64: ScheduledBanRegistry avoids re-applying already-applied due bans
# =============================================================================
echo "--- CHECK 64: ScheduledBanRegistry detects already-applied due bans ---"

SCHED_CPP_CHECK64="$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"

if [[ -z "$SCHED_CPP_CHECK64" ]]; then
    fail "CHECK 64 – ScheduledBanRegistry.cpp not found"
else
    if ! grep -qP 'MatchesScheduledBan' "$SCHED_CPP_CHECK64"; then
        fail "CHECK 64 – ScheduledBanRegistry missing already-applied match helper" \
            "File: $SCHED_CPP_CHECK64"
    fi
    if ! grep -qP 'IsCurrentlyBanned\(Entry\.Uid,\s*Existing\)\s*&&\s*MatchesScheduledBan\(Existing,\s*Entry\)' "$SCHED_CPP_CHECK64"; then
        fail "CHECK 64 – ApplyScheduledBan does not detect already-applied bans before re-applying" \
            "File: $SCHED_CPP_CHECK64"
    fi
fi

pass "CHECK 64 done"
echo

# =============================================================================
# CHECK 65: BanSyncClient updates existing peer bans in place
# =============================================================================
echo "--- CHECK 65: BanSyncClient uses UpdateBan for peer ban edits ---"

BANSYNC_CPP_CHECK65="$(list_cpp_files | tr '\0' '\n' | grep 'BanSyncClient\.cpp' | head -1)"

if [[ -z "$BANSYNC_CPP_CHECK65" ]]; then
    fail "CHECK 65 – BanSyncClient.cpp not found"
else
    if ! grep -qP 'DB->UpdateBan\(' "$BANSYNC_CPP_CHECK65"; then
        fail "CHECK 65 – BanSyncClient does not update existing peer bans in place" \
            "File: $BANSYNC_CPP_CHECK65"
    fi
fi

pass "CHECK 65 done"
echo

# =============================================================================
# CHECK 66: POST /scheduled rejects failed AddScheduled writes
# =============================================================================
echo "--- CHECK 66: POST /scheduled rejects AddScheduled failures ---"

BANREST_CPP_CHECK66="$BANREST_CPP_CHECK57"

if [[ -z "$BANREST_CPP_CHECK66" ]]; then
    fail "CHECK 66 – BanRestApi.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /AddScheduled\s*\([^;]+\);\s*if\s*\(\s*NewEntry\.Id\s*<=\s*0\s*\)\s*\{[^}]*Failed to create scheduled ban/s; exit 1' "$BANREST_CPP_CHECK66"; then
        fail "CHECK 66 – POST /scheduled does not reject AddScheduled failure" \
            "File: $BANREST_CPP_CHECK66"
    fi
fi

pass "CHECK 66 done"
echo

# =============================================================================
# CHECK 67: Whitelist mutations persist audit entries in the same save
# =============================================================================
echo "--- CHECK 67: WhitelistManager persists audit entries atomically with mutations ---"

WM_CPP_CHECK67="$WM_CPP_CHECK61"

if [[ -z "$WM_CPP_CHECK67" ]]; then
    fail "CHECK 67 – WhitelistManager.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /SetEnabled.*?OriginalAuditLog\s*=\s*AuditLog.*?LogAudit\(.*?Save_Locked\(\).*?AuditLog\s*=\s*OriginalAuditLog/s; exit 1' "$WM_CPP_CHECK67"; then
        fail "CHECK 67 – SetEnabled does not roll back persisted audit state on save failure" \
            "File: $WM_CPP_CHECK67"
    fi
    if ! perl -0777 -ne 'exit 0 if /AddPlayer.*?OriginalAuditLog\s*=\s*AuditLog.*?LogAudit\(.*?if\s*\(!Save_Locked\(\)\).*?AuditLog\s*=\s*OriginalAuditLog/s; exit 1' "$WM_CPP_CHECK67"; then
        fail "CHECK 67 – AddPlayer does not persist/rollback audit entries atomically" \
            "File: $WM_CPP_CHECK67"
    fi
    if ! perl -0777 -ne 'exit 0 if /RemovePlayer.*?OriginalAuditLog\s*=\s*AuditLog.*?LogAudit\(.*?if\s*\(!Save_Locked\(\)\).*?AuditLog\s*=\s*OriginalAuditLog/s; exit 1' "$WM_CPP_CHECK67"; then
        fail "CHECK 67 – RemovePlayer does not persist/rollback audit entries atomically" \
            "File: $WM_CPP_CHECK67"
    fi
fi

pass "CHECK 67 done"
echo

# =============================================================================
# CHECK 68: reconnect flush preserves queued messages on enqueue failure
# =============================================================================
echo "--- CHECK 68: SMLWebSocketClient keeps queued messages that fail reconnect flush ---"

WSCLIENT_CPP_CHECK68="$(list_cpp_files | tr '\0' '\n' | grep 'SMLWebSocketClient\.cpp' | head -1)"

if [[ -z "$WSCLIENT_CPP_CHECK68" ]]; then
    fail "CHECK 68 – SMLWebSocketClient.cpp not found"
else
    if ! grep -qP 'RemainingTextQueue' "$WSCLIENT_CPP_CHECK68" || ! grep -qP 'PendingSendQueue\s*=\s*MoveTemp\(RemainingTextQueue\)' "$WSCLIENT_CPP_CHECK68"; then
        fail "CHECK 68 – reconnect text flush still drops unsent queued messages" \
            "File: $WSCLIENT_CPP_CHECK68"
    fi
    if ! grep -qP 'RemainingBinaryQueue' "$WSCLIENT_CPP_CHECK68" || ! grep -qP 'PendingSendBinaryQueue\s*=\s*MoveTemp\(RemainingBinaryQueue\)' "$WSCLIENT_CPP_CHECK68"; then
        fail "CHECK 68 – reconnect binary flush still drops unsent queued messages" \
            "File: $WSCLIENT_CPP_CHECK68"
    fi
fi

pass "CHECK 68 done"
echo

# =============================================================================
# CHECK 69: nextId loaders preserve the exhausted 0 sentinel
# =============================================================================
echo "--- CHECK 69: nextId loaders preserve 0 as the exhausted sentinel ---"

if grep -RP '\(Parsed > 0\) \? Parsed : 1' "${MOD_PATHS[@]}" >/dev/null 2>&1 \
    || grep -RP 'FMath::Max\(\(int64\)1' "${MOD_PATHS[@]}" >/dev/null 2>&1; then
    fail "CHECK 69 – nextId loader still rewrites exhausted sentinel 0 to 1" \
        "Fix: accept stored 0 as the exhausted sentinel instead of clamping to 1."
fi

if ! grep -qP 'bHadStoredNextId' "$AUDITLOG_CPP_CHECK36" 2>/dev/null; then
    fail "CHECK 69 – BanAuditLog does not preserve persisted nextId=0" \
        "File: $AUDITLOG_CPP_CHECK36"
fi

pass "CHECK 69 done"
echo

# =============================================================================
# CHECK 70: Whitelist RemoveExpiredEntries rolls back Entries and suppresses output on save failure
# =============================================================================
echo "--- CHECK 70: Whitelist RemoveExpiredEntries rollback + output suppression on Save_Locked failure ---"

WM_CPP_CHECK70="$(list_cpp_files | tr '\0' '\n' | grep 'WhitelistManager\.cpp' | head -1)"

if [[ -z "$WM_CPP_CHECK70" ]]; then
    fail "CHECK 70 – WhitelistManager.cpp not found"
else
    if ! grep -qP 'const\s+TArray<FWhitelistEntry>\s+PrevEntries\s*=\s*Entries' "$WM_CPP_CHECK70"; then
        fail "CHECK 70 – RemoveExpiredEntries does not snapshot Entries before mutation" \
            "File: $WM_CPP_CHECK70"
    fi

    if ! grep -qP 'Removed\s*>\s*0\s*&&\s*!Save_Locked\(\)' "$WM_CPP_CHECK70"; then
        fail "CHECK 70 – RemoveExpiredEntries has no Save_Locked failure branch after removals" \
            "File: $WM_CPP_CHECK70"
    fi

    if ! perl -0777 -ne 'exit 0 if /if\s*\(\s*Removed\s*>\s*0\s*&&\s*!Save_Locked\(\)\s*\)\s*\{[^}]*Entries\s*=\s*PrevEntries/s; exit 1' "$WM_CPP_CHECK70"; then
        fail "CHECK 70 – RemoveExpiredEntries does not restore Entries from PrevEntries on save failure" \
            "File: $WM_CPP_CHECK70"
    fi

    if ! perl -0777 -ne 'exit 0 if /if\s*\(\s*Removed\s*>\s*0\s*&&\s*!Save_Locked\(\)\s*\)\s*\{[^}]*OutExpiredNames\.Reset\s*\(\s*\)/s; exit 1' "$WM_CPP_CHECK70"; then
        fail "CHECK 70 – RemoveExpiredEntries does not clear OutExpiredNames on save failure" \
            "File: $WM_CPP_CHECK70"
    fi
fi

pass "CHECK 70 done"
echo

# =============================================================================
# CHECK 71: manual FlushQueue preserves queued messages on enqueue failure
# =============================================================================
echo "--- CHECK 71: SMLWebSocketClient FlushQueue keeps unsent queued messages ---"

WSCLIENT_CPP_CHECK71="$(list_cpp_files | tr '\0' '\n' | grep 'SMLWebSocketClient\.cpp' | head -1)"

if [[ -z "$WSCLIENT_CPP_CHECK71" ]]; then
    fail "CHECK 71 – SMLWebSocketClient.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /void\s+USMLWebSocketClient::FlushQueue\s*\(\)\s*\{.*?RemainingTextQueue.*?PendingSendQueue\s*=\s*MoveTemp\(RemainingTextQueue\)/s; exit 1' "$WSCLIENT_CPP_CHECK71"; then
        fail "CHECK 71 – FlushQueue text path still drops unsent messages" \
            "File: $WSCLIENT_CPP_CHECK71"
    fi
    if ! perl -0777 -ne 'exit 0 if /void\s+USMLWebSocketClient::FlushQueue\s*\(\)\s*\{.*?RemainingBinaryQueue.*?PendingSendBinaryQueue\s*=\s*MoveTemp\(RemainingBinaryQueue\)/s; exit 1' "$WSCLIENT_CPP_CHECK71"; then
        fail "CHECK 71 – FlushQueue binary path still drops unsent messages" \
            "File: $WSCLIENT_CPP_CHECK71"
    fi
fi

pass "CHECK 71 done"
echo

# =============================================================================
# CHECK 72: BanWebSocketPusher PushEvent enforces game-thread dispatch
# =============================================================================
echo "--- CHECK 72: BanWebSocketPusher PushEvent dispatches to game thread ---"

PUSHER_CPP_CHECK72="$(list_cpp_files | tr '\0' '\n' | grep 'BanWebSocketPusher\.cpp' | head -1)"

if [[ -z "$PUSHER_CPP_CHECK72" ]]; then
    fail "CHECK 72 – BanWebSocketPusher.cpp not found"
else
    if ! grep -qP 'if\s*\(\s*!IsInGameThread\(\)\s*\)' "$PUSHER_CPP_CHECK72"; then
        fail "CHECK 72 – PushEvent missing non-game-thread dispatch guard" \
            "File: $PUSHER_CPP_CHECK72" \
            "Fix: early-guard with IsInGameThread() and AsyncTask(ENamedThreads::GameThread, ...)."
    fi

    if ! grep -qP 'AsyncTask\s*\(\s*ENamedThreads::GameThread' "$PUSHER_CPP_CHECK72"; then
        fail "CHECK 72 – PushEvent missing AsyncTask(ENamedThreads::GameThread, ...) dispatch" \
            "File: $PUSHER_CPP_CHECK72"
    fi

    if ! perl -0777 -ne 'exit 0 if /if\s*\(\s*!IsInGameThread\(\)\s*\)\s*\{[\s\S]*?AsyncTask\s*\(\s*ENamedThreads::GameThread[\s\S]*?\breturn\s*;[\s\S]*?\}\s*UBanWebSocketPusher\*\s+Self\s*=\s*ActiveInstance\.Get\s*\(\s*\)\s*;/s; exit 1' "$PUSHER_CPP_CHECK72"; then
        fail "CHECK 72 – PushEvent must return from the non-game-thread guard before ActiveInstance access" \
            "File: $PUSHER_CPP_CHECK72"
    fi
fi

pass "CHECK 72 done"
echo

# =============================================================================
# CHECK 73: BanDatabase AddBan/AddBanSkipIfPermanentExists restores OldEntry on NextId==0
# =============================================================================
echo "--- CHECK 73: BanDatabase restores OldEntry when NextId is exhausted ---"

BANDB_CPP_CHECK73="$(list_cpp_files | tr '\0' '\n' | grep 'BanDatabase\.cpp' | head -1)"

if [[ -z "$BANDB_CPP_CHECK73" ]]; then
    fail "CHECK 73 – BanDatabase.cpp not found"
else
    # Verify all three AddBan overloads restore OldEntry before the NextId==0 early return.
    # The Perl check reads the whole file and counts the pattern across line boundaries.
    if ! perl -0777 -ne '
        my $src = $_;
        my $hits = () = $src =~ /if\s*\(bHadOldEntry\)\s*Bans\.Add\(OldEntry\);\s*\n\s*UE_LOG\(LogBanDatabase[^)]*all 64-bit IDs/g;
        exit 0 if $hits >= 3;
        exit 1;
    ' "$BANDB_CPP_CHECK73"; then
        fail "CHECK 73 – AddBan/AddBanSkipIfPermanentExists (one or more overloads) missing OldEntry restore before NextId==0 early return" \
            "File: $BANDB_CPP_CHECK73" \
            "Fix: add 'if (bHadOldEntry) Bans.Add(OldEntry);' before each 'return false' in the NextId==0 branch."
    fi
fi

pass "CHECK 73 done"
echo

# =============================================================================
# CHECK 74: ScheduledBanRegistry Tick preserves RetryCount increments on SaveToFile failure
# =============================================================================
echo "--- CHECK 74: ScheduledBanRegistry Tick preserves RetryCount on rollback ---"

SCHED_CPP_CHECK74="$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"

if [[ -z "$SCHED_CPP_CHECK74" ]]; then
    fail "CHECK 74 – ScheduledBanRegistry.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /if\s*\(\s*!SaveToFile\(\)\s*\)[\s\S]*?Prev\.RetryCount\s*=\s*FE\.RetryCount[\s\S]*?Pending\s*=\s*PrevPending/s; exit 1' "$SCHED_CPP_CHECK74"; then
        fail "CHECK 74 – ScheduledBanRegistry Tick rollback overwrites RetryCount increments" \
            "File: $SCHED_CPP_CHECK74" \
            "Fix: carry over updated RetryCount from FailedEntries into PrevPending before restoring Pending."
    fi
fi

pass "CHECK 74 done"
echo

# =============================================================================
# CHECK 75: BanDiscordSubsystem warn escalation uses DurationMinutes comparison
# =============================================================================
echo "--- CHECK 75: BanDiscordSubsystem warn escalation uses DurationMinutes severity comparison ---"

BANDISCORD_CPP_CHECK75="$(list_cpp_files | tr '\0' '\n' | grep 'BanDiscordSubsystem\.cpp' | head -1)"

if [[ -z "$BANDISCORD_CPP_CHECK75" ]]; then
    fail "CHECK 75 – BanDiscordSubsystem.cpp not found"
else
    # Must NOT contain the old BestThreshold pattern in warn escalation blocks
    if grep -qP '^\s*int32\s+BestThreshold\s*=\s*-1;' "$BANDISCORD_CPP_CHECK75"; then
        fail "CHECK 75 – BanDiscordSubsystem still uses stale BestThreshold algorithm in warn escalation" \
            "File: $BANDISCORD_CPP_CHECK75" \
            "Fix: replace BestThreshold comparison with DurationMinutes-severity comparison (same as BanChatCommands.cpp)."
    fi
    # Must contain the DurationMinutes-severity comparison in at least two places (HandleWarnCommand + ExecutePanelWarn)
    COUNT75=$(grep -cP 'const bool bMoreSevere\s*=\s*\(BanDurationMinutes\s*<\s*0\)' "$BANDISCORD_CPP_CHECK75" 2>/dev/null || true)
    COUNT75="${COUNT75:-0}"
    if [[ "$COUNT75" -lt 2 ]]; then
        fail "CHECK 75 – BanDiscordSubsystem warn escalation missing DurationMinutes-severity comparison in one or both warn paths" \
            "File: $BANDISCORD_CPP_CHECK75" \
            "Fix: apply the DurationMinutes-severity comparison to both HandleWarnCommand and ExecutePanelWarn."
    fi
fi

pass "CHECK 75 done"
echo

# =============================================================================
# CHECK 76: Discord interaction numeric "type" fields are parsed via guarded double->int conversion
# =============================================================================
echo "--- CHECK 76: interaction type parsing uses finite/range/integer guards ---"

BANDISCORD_CPP_FILE="$(list_cpp_files | tr '\0' '\n' | grep 'BanDiscordSubsystem\.cpp' | head -1)"
TICKET_CPP_FILE="$(list_cpp_files | tr '\0' '\n' | grep 'TicketSubsystem\.cpp' | head -1)"
BRIDGE_CPP_FILE="$(list_cpp_files | tr '\0' '\n' | grep 'DiscordBridgeSubsystem\.cpp' | head -1)"

if [[ -z "$BANDISCORD_CPP_FILE" ]]; then
    fail "CHECK 76 – BanDiscordSubsystem.cpp not found"
else
    if grep -qP 'TryGetNumberField\s*\(\s*TEXT\("type"\)\s*,\s*InteractionType\s*\)' "$BANDISCORD_CPP_FILE"; then
        fail "CHECK 76 – BanDiscordSubsystem uses direct TryGetNumberField(..., int32 InteractionType) parse" \
            "File: $BANDISCORD_CPP_FILE" \
            "Fix: parse into double, then gate cast with IsFinite/range/integer checks."
    fi
    if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\s*\(\s*TEXT\("type"\)\s*,\s*(\w+)\s*\)\s*;[\s\S]{0,500}?const\s+int32\s+\w+\s*=\s*\([\s\S]{0,300}?FMath::IsFinite\s*\(\s*\1\s*\)[\s\S]{0,300}?FMath::Fmod\s*\(\s*\1\s*,\s*1\.0\s*\)\s*==\s*0\.0/s; exit 1' "$BANDISCORD_CPP_FILE"; then
        fail "CHECK 76 – BanDiscordSubsystem missing guarded interaction type parse" \
            "File: $BANDISCORD_CPP_FILE"
    fi
fi

if [[ -z "$TICKET_CPP_FILE" ]]; then
    fail "CHECK 76 – TicketSubsystem.cpp not found"
else
    if grep -qP 'TryGetNumberField\s*\(\s*TEXT\("type"\)\s*,\s*InteractionType\s*\)' "$TICKET_CPP_FILE"; then
        fail "CHECK 76 – TicketSubsystem uses direct TryGetNumberField(..., int32 InteractionType) parse in slash handler" \
            "File: $TICKET_CPP_FILE" \
            "Fix: parse into double, then gate cast with IsFinite/range/integer checks."
    fi
    if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\s*\(\s*TEXT\("type"\)\s*,\s*(\w+)\s*\)\s*;[\s\S]{0,500}?const\s+int32\s+\w+\s*=\s*\([\s\S]{0,300}?FMath::IsFinite\s*\(\s*\1\s*\)[\s\S]{0,300}?FMath::Fmod\s*\(\s*\1\s*,\s*1\.0\s*\)\s*==\s*0\.0/s; exit 1' "$TICKET_CPP_FILE"; then
        fail "CHECK 76 – TicketSubsystem missing guarded slash interaction type parse" \
            "File: $TICKET_CPP_FILE"
    fi
fi

if [[ -z "$BRIDGE_CPP_FILE" ]]; then
    fail "CHECK 76 – DiscordBridgeSubsystem.cpp not found"
else
    if grep -qP 'TryGetNumberField\s*\(\s*TEXT\("type"\)\s*,\s*InteractionType\s*\)' "$BRIDGE_CPP_FILE"; then
        fail "CHECK 76 – DiscordBridgeSubsystem uses direct TryGetNumberField(..., int32 InteractionType) parse" \
            "File: $BRIDGE_CPP_FILE" \
            "Fix: parse into double, then gate cast with IsFinite/range/integer checks."
    fi
    if grep -qP 'if\s*\(\s*static_cast<int32>\s*\(\s*OptType\s*\)\s*==\s*1\s*\)' "$BRIDGE_CPP_FILE"; then
        fail "CHECK 76 – DiscordBridgeSubsystem autocomplete path casts OptType without finite/range/integer guard" \
            "File: $BRIDGE_CPP_FILE" \
            "Fix: derive OptTypeInt through guarded conversion before comparing to SUB_COMMAND."
    fi
    if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\s*\(\s*TEXT\("type"\)\s*,\s*(\w+)\s*\)\s*;[\s\S]{0,500}?const\s+int32\s+\w+\s*=\s*\([\s\S]{0,300}?FMath::IsFinite\s*\(\s*\1\s*\)[\s\S]{0,300}?FMath::Fmod\s*\(\s*\1\s*,\s*1\.0\s*\)\s*==\s*0\.0/s; exit 1' "$BRIDGE_CPP_FILE"; then
        fail "CHECK 76 – DiscordBridgeSubsystem missing guarded OptTypeInt conversion in autocomplete path" \
            "File: $BRIDGE_CPP_FILE"
    fi
fi

pass "CHECK 76 done"
echo

# =============================================================================
# CHECK 77: durationMinutes positive cast uses FMath::Max(1, ...) to prevent
#           fractional values (0 < x < 1) from silently truncating to 0 and
#           becoming a permanent ban.
#
# All ban-creation / ban-edit paths in BanRestApi.cpp that have a
# "static_cast<int32>(DurationMinutesDbl)" (or DurDbl) in the positive branch
# must be accompanied by a FMath::Max(1, ...) guard on the same or adjacent
# line.  A bare static_cast in that path is a bug.
# =============================================================================
echo "--- CHECK 77: durationMinutes positive cast guarded with FMath::Max(1,...) ---"

BANRESTAPI_CPP="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$BANRESTAPI_CPP" ]]; then
    fail "CHECK 77 – BanRestApi.cpp not found"
else
    # Detect any bare static_cast<int32>(DurationMinutesDbl) or static_cast<int32>(DurDbl)
    # that is NOT on the same line as FMath::Max(1, .
    while IFS= read -r ln; do
        lineno="${ln%%:*}"
        content="${ln#*:}"
        # Does the line have the cast but NOT Max(1, ?
        if echo "$content" | grep -qP 'static_cast<int32>\s*\(\s*(DurationMinutesDbl|DurDbl)\s*\)' \
           && ! echo "$content" | grep -qP 'FMath::Max\s*\(\s*1\s*,'; then
            fail "CHECK 77 – bare durationMinutes cast without FMath::Max(1,...)" \
                "File: $BANRESTAPI_CPP  Line $lineno: $content" \
                "Fix: use FMath::Max(1, static_cast<int32>(DurDbl)) in the positive-value branch."
        fi
    done < <(grep -n 'static_cast<int32>\s*(\(DurationMinutesDbl\|DurDbl\))' "$BANRESTAPI_CPP" 2>/dev/null || true)
fi

pass "CHECK 77 done"
echo

# =============================================================================
# CHECK 78: BanSyncClient durationMinutes receiver uses FMath::IsFinite guard
#
# The incoming durationMinutes field from a sync peer is a JSON double and
# must be guarded with FMath::IsFinite before the comparison with INT32_MAX,
# otherwise a NaN value evades the > 0 check and INT32_MAX bounds check,
# potentially causing UB in the static_cast.
# =============================================================================
echo "--- CHECK 78: BanSyncClient durationMinutes receiver has FMath::IsFinite guard ---"

BANSYNC_CPP="$(list_cpp_files | tr '\0' '\n' | grep 'BanSyncClient\.cpp' | head -1)"

if [[ -z "$BANSYNC_CPP" ]]; then
    fail "CHECK 78 – BanSyncClient.cpp not found"
else
    # Look for the durationMinutes ternary.  It must contain IsFinite.
    if grep -qP 'TryGetNumberField.*durationMinutes' "$BANSYNC_CPP"; then
        # The ternary that converts DurDbl to int32 must use IsFinite.
        if ! perl -0777 -ne '
            exit 0 if /TryGetNumberField.*"durationMinutes".*[\s\S]{0,300}?FMath::IsFinite.*DurDbl/s;
            exit 1' "$BANSYNC_CPP"; then
            fail "CHECK 78 – BanSyncClient durationMinutes parse missing FMath::IsFinite guard" \
                "File: $BANSYNC_CPP" \
                "Fix: add FMath::IsFinite(DurDbl) to the ternary condition."
        fi
        # Must also use FMath::Max(1, ...) in the positive branch.
        if ! perl -0777 -ne '
            exit 0 if /TryGetNumberField.*"durationMinutes".*[\s\S]{0,400}?FMath::Max\s*\(\s*1\s*,/s;
            exit 1' "$BANSYNC_CPP"; then
            fail "CHECK 78 – BanSyncClient durationMinutes cast missing FMath::Max(1,...)" \
                "File: $BANSYNC_CPP" \
                "Fix: use FMath::Max(1, static_cast<int32>(DurDbl)) to prevent fractional-floor-to-permanent."
        fi
    fi
fi

pass "CHECK 78 done"
echo

# =============================================================================
# CHECK 79: TicketSubsystem OnInteractionReceived type field uses Fmod guard
#
# The interaction type field in OnInteractionReceived must use the same full
# finite/range/integer guard as the other three parse sites (HandleSlashTicketCommand,
# BanDiscordSubsystem, DiscordBridgeSubsystem).
# =============================================================================
echo "--- CHECK 79: TicketSubsystem OnInteractionReceived type parse uses Fmod guard ---"

TICKET_CPP_FILE79="$(list_cpp_files | tr '\0' '\n' | grep 'TicketSubsystem\.cpp' | head -1)"

if [[ -z "$TICKET_CPP_FILE79" ]]; then
    fail "CHECK 79 – TicketSubsystem.cpp not found"
else
    # OnInteractionReceived's type parse must have Fmod guard.
    if ! perl -0777 -ne '
        exit 0 if /OnInteractionReceived[\s\S]{0,600}?FMath::Fmod\s*\(\s*TypeD\s*,\s*1\.0\s*\)\s*==\s*0\.0/s;
        exit 1' "$TICKET_CPP_FILE79"; then
        fail "CHECK 79 – TicketSubsystem::OnInteractionReceived type parse missing Fmod guard" \
            "File: $TICKET_CPP_FILE79" \
            "Fix: add '&& FMath::Fmod(TypeD, 1.0) == 0.0' to the InteractionType cast condition."
    fi
fi

pass "CHECK 79 done"
echo

# =============================================================================
# CHECK 80: Gateway opcode parse uses Fmod guard
#
# The Discord gateway opcode parse in DiscordBridgeSubsystem must reject
# fractional opcode values via FMath::Fmod guard, consistent with the
# comment in the same code that says non-integer opcodes are malformed.
# =============================================================================
echo "--- CHECK 80: DiscordBridgeSubsystem gateway opcode uses Fmod guard ---"

BRIDGE_CPP_FILE80="$(list_cpp_files | tr '\0' '\n' | grep 'DiscordBridgeSubsystem\.cpp' | head -1)"

if [[ -z "$BRIDGE_CPP_FILE80" ]]; then
    fail "CHECK 80 – DiscordBridgeSubsystem.cpp not found"
else
    if ! perl -0777 -ne '
        exit 0 if /TryGetNumberField.*"op".*[\s\S]{0,600}?FMath::Fmod\s*\(\s*OpCodeD\s*,\s*1\.0\s*\)/s;
        exit 1' "$BRIDGE_CPP_FILE80"; then
        fail "CHECK 80 – DiscordBridgeSubsystem opcode parse missing Fmod integer guard" \
            "File: $BRIDGE_CPP_FILE80" \
            "Fix: add '|| FMath::Fmod(OpCodeD, 1.0) != 0.0' to the opcode range-check condition."
    fi
fi

pass "CHECK 80 done"
echo


# =============================================================================
# CHECK 81: BanRestApi ConstantTimeEquals always iterates at least 256 bytes
# =============================================================================
echo "--- CHECK 81: ConstantTimeEquals iterates at least 256 bytes ---"

RESTAPI_CPP_FILE81="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$RESTAPI_CPP_FILE81" ]]; then
    fail "CHECK 81 – BanRestApi.cpp not found"
elif ! grep -qP 'FMath::Max.*256|Max.*256.*Length' "$RESTAPI_CPP_FILE81"; then
    fail "CHECK 81 – ConstantTimeEquals does not enforce a minimum iteration count of 256" \
        "File: $RESTAPI_CPP_FILE81" \
        "Fix: use FMath::Max(FMath::Max(Au.Length(), Bu.Length()), 256) for N."
fi

pass "CHECK 81 done"
echo

# =============================================================================
# CHECK 82: BanRestApi DELETE /appeals checks ReviewAppeal return value
# =============================================================================
echo "--- CHECK 82: DELETE /appeals checks ReviewAppeal return ---"

RESTAPI_CPP_FILE82="$RESTAPI_CPP_FILE81"

if [[ -z "$RESTAPI_CPP_FILE82" ]]; then
    fail "CHECK 82 – BanRestApi.cpp not found"
elif ! grep -qP '!\s*AppealsReg->ReviewAppeal' "$RESTAPI_CPP_FILE82"; then
    fail "CHECK 82 – DELETE /appeals does not check ReviewAppeal return value" \
        "File: $RESTAPI_CPP_FILE82" \
        "Fix: wrap ReviewAppeal(...) in 'if (!...)' and return an error on failure."
fi

pass "CHECK 82 done"
echo

# =============================================================================
# CHECK 83: BanRestApi POST /appeals rate limit uses TSharedPtr (not static)
# =============================================================================
echo "--- CHECK 83: POST /appeals rate-limit state captured in TSharedPtr ---"

RESTAPI_CPP_FILE83="$RESTAPI_CPP_FILE81"

if [[ -z "$RESTAPI_CPP_FILE83" ]]; then
    fail "CHECK 83 – BanRestApi.cpp not found"
elif grep -qP '^\s+static\s+(TArray|FCriticalSection)\s+(AppealSubmissions|AppealRateMutex)' "$RESTAPI_CPP_FILE83"; then
    fail "CHECK 83 – POST /appeals rate-limit still uses process-lifetime static variables" \
        "File: $RESTAPI_CPP_FILE83" \
        "Fix: wrap rate-limit state in a TSharedPtr captured at route registration time."
fi

pass "CHECK 83 done"
echo

# =============================================================================
# CHECK 84: BanRestApi PATCH /appeals reads appeal Uid before ReviewAppeal
# =============================================================================
echo "--- CHECK 84: PATCH /appeals reads appeal Uid before ReviewAppeal (TOCTOU fix) ---"

RESTAPI_CPP_FILE84="$RESTAPI_CPP_FILE81"

if [[ -z "$RESTAPI_CPP_FILE84" ]]; then
    fail "CHECK 84 – BanRestApi.cpp not found"
elif ! grep -qP 'PreReviewAppeal\s*=\s*AppealsReg->GetAppealById' "$RESTAPI_CPP_FILE84"; then
    fail "CHECK 84 – PATCH /appeals does not capture appeal before ReviewAppeal" \
        "File: $RESTAPI_CPP_FILE84" \
        "Fix: call GetAppealById(Id) before ReviewAppeal to avoid TOCTOU on auto-unban."
fi

pass "CHECK 84 done"
echo

# =============================================================================
# CHECK 85: BanDiscordSubsystem Discord→in-game relay caps message length
# =============================================================================
echo "--- CHECK 85: Discord→in-game relay caps message length ---"

BDISCORD_CPP_FILE85="$(list_cpp_files | tr '\0' '\n' | grep 'BanDiscordSubsystem\.cpp' | head -1)"

if [[ -z "$BDISCORD_CPP_FILE85" ]]; then
    fail "CHECK 85 – BanDiscordSubsystem.cpp not found"
elif ! grep -qP 'MaxRelayLength|RelayMsg' "$BDISCORD_CPP_FILE85"; then
    fail "CHECK 85 – Discord→in-game relay does not cap message length" \
        "File: $BDISCORD_CPP_FILE85" \
        "Fix: truncate Formatted to MaxRelayLength before calling PC->ClientMessage."
fi

pass "CHECK 85 done"
echo

# =============================================================================
# CHECK 86: BanEnforcer kick timers stored in PendingKickTimersByUid
# =============================================================================
echo "--- CHECK 86: BanEnforcer kick timers stored for cancellation on unban ---"

ENFORCER_CPP_FILE86="$(list_cpp_files | tr '\0' '\n' | grep 'BanEnforcer\.cpp' | head -1)"

if [[ -z "$ENFORCER_CPP_FILE86" ]]; then
    fail "CHECK 86 – BanEnforcer.cpp not found"
elif ! grep -qP 'PendingKickTimersByUid' "$ENFORCER_CPP_FILE86"; then
    fail "CHECK 86 – BanEnforcer does not store kick timer handles for cancellation" \
        "File: $ENFORCER_CPP_FILE86" \
        "Fix: add TMap<FString,FTimerHandle> PendingKickTimersByUid and cancel on OnBanRemoved."
fi

pass "CHECK 86 done"
echo

# =============================================================================
# CHECK 87: BanEnforcer OnBanRemoved cancels PendingKickTimersByUid entry
# =============================================================================
echo "--- CHECK 87: BanEnforcer OnBanRemoved cancels pending kick timer ---"

ENFORCER_CPP_FILE87="$ENFORCER_CPP_FILE86"

if [[ -z "$ENFORCER_CPP_FILE87" ]]; then
    fail "CHECK 87 – BanEnforcer.cpp not found"
elif ! perl -0777 -ne '
    exit 0 if /PendingKickTimersByUid\.Find\s*\(\s*Uid\s*\)[\s\S]{0,400}?ClearTimer/s;
    exit 1' "$ENFORCER_CPP_FILE87"; then
    fail "CHECK 87 – BanEnforcer OnBanRemoved does not cancel kick timer via PendingKickTimersByUid" \
        "File: $ENFORCER_CPP_FILE87" \
        "Fix: in OnBanRemoved, call World->GetTimerManager().ClearTimer for the PendingKickTimersByUid entry."
fi

pass "CHECK 87 done"
echo

# =============================================================================
# CHECK 88: BanAuditLog rollback uses lightweight per-entry state (not full copy)
# =============================================================================
echo "--- CHECK 88: BanAuditLog rollback uses lightweight TrimmedEntries (not full PrevEntries copy) ---"

AUDITLOG_CPP_FILE88="$(list_cpp_files | tr '\0' '\n' | grep 'BanAuditLog\.cpp' | head -1)"

if [[ -z "$AUDITLOG_CPP_FILE88" ]]; then
    fail "CHECK 88 – BanAuditLog.cpp not found"
elif grep -qP 'const\s+TArray<FAuditEntry>\s+PrevEntries\s*=' "$AUDITLOG_CPP_FILE88"; then
    fail "CHECK 88 – BanAuditLog still uses full-array O(n) PrevEntries rollback copy" \
        "File: $AUDITLOG_CPP_FILE88" \
        "Fix: replace PrevEntries with TrimmedEntries + Entries.RemoveAt(Num()-1) lightweight rollback."
fi

pass "CHECK 88 done"
echo


# =============================================================================
# CHECK 89: POST /warnings aborts on AddWarning persistence failure
# =============================================================================
echo "--- CHECK 89: POST /warnings checks AddWarning() result before side effects ---"

BANRESTAPI_CPP_FILE89="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$BANRESTAPI_CPP_FILE89" ]]; then
    fail "CHECK 89 – BanRestApi.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /const\s+FWarningEntry\s+NewEntry\s*=\s*WarnReg->AddWarning\s*\(\s*NewWarnEntry\s*\)\s*;[\s\S]{0,250}?if\s*\(\s*NewEntry\.Id\s*==\s*0\s*\)[\s\S]{0,250}?return\s+true\s*;/s; exit 1' "$BANRESTAPI_CPP_FILE89"; then
        fail "CHECK 89 – POST /warnings still ignores AddWarning save failure" \
            "File: $BANRESTAPI_CPP_FILE89" \
            "Fix: if NewEntry.Id == 0, return HTTP 500 before notifications, audit log, or auto-ban side effects."
    fi
fi

pass "CHECK 89 done"
echo

# =============================================================================
# CHECK 90: POST /warnings warn escalation uses DurationMinutes severity comparison
# =============================================================================
echo "--- CHECK 90: POST /warnings warn escalation uses DurationMinutes severity comparison ---"

BANRESTAPI_CPP_FILE90="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"

if [[ -z "$BANRESTAPI_CPP_FILE90" ]]; then
    fail "CHECK 90 – BanRestApi.cpp not found"
else
    if grep -qP '\bBestThreshold\b' "$BANRESTAPI_CPP_FILE90"; then
        fail "CHECK 90 – BanRestApi warn escalation still uses stale BestThreshold algorithm" \
            "File: $BANRESTAPI_CPP_FILE90" \
            "Fix: compare matching tiers by DurationMinutes severity (0 = permanent, otherwise longest duration wins)."
    fi
    if ! perl -0777 -ne 'exit 0 if /WarnEscalationTiers\.Num\(\)\s*>\s*0[\s\S]{0,1200}?const\s+bool\s+bMoreSevere\s*=\s*\(BanDurationMinutes\s*<\s*0\)[\s\S]{0,300}?Tier\.DurationMinutes\s*==\s*0[\s\S]{0,300}?Tier\.DurationMinutes\s*>\s*BanDurationMinutes/s; exit 1' "$BANRESTAPI_CPP_FILE90"; then
        fail "CHECK 90 – BanRestApi warn escalation missing DurationMinutes-severity comparison" \
            "File: $BANRESTAPI_CPP_FILE90"
    fi
fi

pass "CHECK 90 done"
echo

# =============================================================================
# CHECK 91: SMLWebSocket reconnect flush preserves outbound FIFO ordering
# =============================================================================
echo "--- CHECK 91: reconnect flush preserves the failed head outbound message ---"

SMLWSRUN_CPP_FILE91="$(list_cpp_files | tr '\0' '\n' | grep 'SMLWebSocketRunnable\.cpp' | head -1)"
SMLWSRUN_H_FILE91="$(list_header_files | tr '\0' '\n' | grep 'SMLWebSocketRunnable\.h' | head -1)"

if [[ -z "$SMLWSRUN_CPP_FILE91" || -z "$SMLWSRUN_H_FILE91" ]]; then
    fail "CHECK 91 – SMLWebSocketRunnable source/header not found"
else
    if ! grep -q 'PendingRetryMessage' "$SMLWSRUN_H_FILE91"; then
        fail "CHECK 91 – SMLWebSocketRunnable.h missing PendingRetryMessage head-of-line buffer" \
            "File: $SMLWSRUN_H_FILE91" \
            "Fix: store the failed head outbound message separately so reconnect retries it before later queue entries."
    fi
    if perl -0777 -ne 'exit 0 if /SendWsFrame failed in FlushOutboundQueue[\s\S]{0,400}?OutboundMessages\.Enqueue\s*\(\s*MoveTemp\(Msg\)\s*\)/s; exit 1' "$SMLWSRUN_CPP_FILE91"; then
        fail "CHECK 91 – FlushOutboundQueue still re-enqueues failed head message at queue tail" \
            "File: $SMLWSRUN_CPP_FILE91" \
            "Fix: preserve the failed message in PendingRetryMessage instead of OutboundMessages.Enqueue(MoveTemp(Msg))."
    fi
    if ! perl -0777 -ne 'exit 0 if /if\s*\(\s*bHasPendingRetryMessage\s*\)[\s\S]{0,600}?SendWsFrame[\s\S]{0,600}?PendingRetryMessage\s*=\s*MoveTemp\(Msg\)\s*;[\s\S]{0,200}?bHasPendingRetryMessage\s*=\s*true/s; exit 1' "$SMLWSRUN_CPP_FILE91"; then
        fail "CHECK 91 – FlushOutboundQueue missing head-of-line retry preservation logic" \
            "File: $SMLWSRUN_CPP_FILE91"
    fi
fi

pass "CHECK 91 done"
echo

# =============================================================================
# CHECK 92: WebSocket server handshake uses a short recv timeout plus wall-clock deadline
# =============================================================================
echo "--- CHECK 92: server handshake has bounded wall-clock stall time ---"

WSSERVER_CPP_FILE92="$(list_cpp_files | tr '\0' '\n' | grep 'SMLWebSocketServerRunnable\.cpp' | head -1)"

if [[ -z "$WSSERVER_CPP_FILE92" ]]; then
    fail "CHECK 92 – SMLWebSocketServerRunnable.cpp not found"
else
    if grep -q 'SetReceiveTimeout(FTimespan::FromSeconds(5))' "$WSSERVER_CPP_FILE92"; then
        fail "CHECK 92 – server handshake still uses a 5-second per-byte receive timeout" \
            "File: $WSSERVER_CPP_FILE92" \
            "Fix: use a short timeout (for example 200 ms) plus an overall handshake wall-clock deadline."
    fi
    if ! grep -q 'HandshakeTimeoutSeconds' "$WSSERVER_CPP_FILE92"; then
        fail "CHECK 92 – server handshake missing overall timeout constant" \
            "File: $WSSERVER_CPP_FILE92"
    fi
    if ! grep -q 'SetReceiveTimeout(FTimespan::FromMilliseconds(200))' "$WSSERVER_CPP_FILE92"; then
        fail "CHECK 92 – server handshake missing short receive timeout" \
            "File: $WSSERVER_CPP_FILE92"
    fi
    if ! grep -q 'HandshakeDeadline' "$WSSERVER_CPP_FILE92"; then
        fail "CHECK 92 – server handshake missing wall-clock deadline check" \
            "File: $WSSERVER_CPP_FILE92"
    fi
fi

pass "CHECK 92 done"
echo


# =============================================================================
# CHECK 93: legacy numeric JSON integer fallbacks reject fractional values
# =============================================================================
echo "--- CHECK 93: legacy numeric JSON integer fallbacks use Fmod guards ---"

if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("id"\),\s*IdDbl\)[\s\S]{0,120}?FMath::Fmod\(IdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int64>\(IdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'BanDatabase\.cpp' | head -1)"; then
    fail "CHECK 93 – BanDatabase legacy numeric id load can still truncate fractional values" \
        "Fix: require FMath::Fmod(IdDbl, 1.0) == 0.0 before static_cast<int64>(IdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("nextId"\),\s*NextIdDbl\)[\s\S]{0,140}?FMath::Fmod\(NextIdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int64>\(NextIdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'BanDatabase\.cpp' | head -1)"; then
    fail "CHECK 93 – BanDatabase legacy numeric nextId load can still truncate fractional values" \
        "Fix: require FMath::Fmod(NextIdDbl, 1.0) == 0.0 before static_cast<int64>(NextIdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("id"\),\s*IdDbl\)[\s\S]{0,120}?FMath::Fmod\(IdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int64>\(IdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'BanAuditLog\.cpp' | head -1)"; then
    fail "CHECK 93 – BanAuditLog legacy numeric id load can still truncate fractional values" \
        "Fix: require FMath::Fmod(IdDbl, 1.0) == 0.0 before static_cast<int64>(IdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("nextId"\),\s*StoredNextId\)[\s\S]{0,160}?FMath::Fmod\(StoredNextId,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,120}?static_cast<int64>\(StoredNextId\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'BanAuditLog\.cpp' | head -1)"; then
    fail "CHECK 93 – BanAuditLog legacy numeric nextId load can still truncate fractional values" \
        "Fix: require FMath::Fmod(StoredNextId, 1.0) == 0.0 before static_cast<int64>(StoredNextId)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("id"\),\s*IdDbl\)[\s\S]{0,120}?FMath::Fmod\(IdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int64>\(IdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'BanAppealRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – BanAppealRegistry legacy numeric id load can still truncate fractional values" \
        "Fix: require FMath::Fmod(IdDbl, 1.0) == 0.0 before static_cast<int64>(IdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("nextId"\),\s*StoredNextIdDbl\)[\s\S]{0,160}?FMath::Fmod\(StoredNextIdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,120}?static_cast<int64>\(StoredNextIdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'BanAppealRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – BanAppealRegistry legacy numeric nextId load can still truncate fractional values" \
        "Fix: require FMath::Fmod(StoredNextIdDbl, 1.0) == 0.0 before static_cast<int64>(StoredNextIdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("id"\),\s*IdDbl\)[\s\S]{0,120}?FMath::Fmod\(IdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int64>\(IdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'PlayerWarningRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – PlayerWarningRegistry legacy numeric id load can still truncate fractional values" \
        "Fix: require FMath::Fmod(IdDbl, 1.0) == 0.0 before static_cast<int64>(IdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("nextId"\),\s*StoredNextIdDbl\)[\s\S]{0,160}?FMath::Fmod\(StoredNextIdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,120}?static_cast<int64>\(StoredNextIdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'PlayerWarningRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – PlayerWarningRegistry legacy numeric nextId load can still truncate fractional values" \
        "Fix: require FMath::Fmod(StoredNextIdDbl, 1.0) == 0.0 before static_cast<int64>(StoredNextIdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("id"\),\s*IdDbl\)[\s\S]{0,120}?FMath::Fmod\(IdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int64>\(IdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – ScheduledBanRegistry legacy numeric id load can still truncate fractional values" \
        "Fix: require FMath::Fmod(IdDbl, 1.0) == 0.0 before static_cast<int64>(IdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("durationMinutes"\),\s*DurDbl\)[\s\S]{0,140}?FMath::Fmod\(DurDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int32>\(DurDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – ScheduledBanRegistry legacy durationMinutes load can still truncate fractional values" \
        "Fix: require FMath::Fmod(DurDbl, 1.0) == 0.0 before static_cast<int32>(DurDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("retryCount"\),\s*RetryDbl\)[\s\S]{0,140}?FMath::Fmod\(RetryDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int32>\(RetryDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – ScheduledBanRegistry legacy retryCount load can still truncate fractional values" \
        "Fix: require FMath::Fmod(RetryDbl, 1.0) == 0.0 before static_cast<int32>(RetryDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("nextId"\),\s*StoredNextIdDbl\)[\s\S]{0,160}?FMath::Fmod\(StoredNextIdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,120}?static_cast<int64>\(StoredNextIdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – ScheduledBanRegistry legacy numeric nextId load can still truncate fractional values" \
        "Fix: require FMath::Fmod(StoredNextIdDbl, 1.0) == 0.0 before static_cast<int64>(StoredNextIdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("id"\),\s*IdDbl\)[\s\S]{0,120}?FMath::Fmod\(IdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,80}?static_cast<int64>\(IdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'PlayerNoteRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – PlayerNoteRegistry legacy numeric id load can still truncate fractional values" \
        "Fix: require FMath::Fmod(IdDbl, 1.0) == 0.0 before static_cast<int64>(IdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("nextId"\),\s*StoredNextIdDbl\)[\s\S]{0,160}?FMath::Fmod\(StoredNextIdDbl,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,120}?static_cast<int64>\(StoredNextIdDbl\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'PlayerNoteRegistry\.cpp' | head -1)"; then
    fail "CHECK 93 – PlayerNoteRegistry legacy numeric nextId load can still truncate fractional values" \
        "Fix: require FMath::Fmod(StoredNextIdDbl, 1.0) == 0.0 before static_cast<int64>(StoredNextIdDbl)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("appeal_id"\),\s*AppealIdLoad\)[\s\S]{0,160}?FMath::Fmod\(AppealIdLoad,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,100}?static_cast<int64>\(AppealIdLoad\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'TicketSubsystem\.cpp' | head -1)"; then
    fail "CHECK 93 – TicketSubsystem legacy numeric appeal_id load can still truncate fractional values" \
        "Fix: require FMath::Fmod(AppealIdLoad, 1.0) == 0.0 before static_cast<int64>(AppealIdLoad)."
fi
if ! perl -0777 -ne 'exit 0 if /TryGetNumberField\(TEXT\("max_slots"\),\s*MaxSlotsD\)[\s\S]{0,160}?FMath::Fmod\(MaxSlotsD,\s*1\.0\)\s*==\s*0\.0[\s\S]{0,100}?static_cast<int32>\(MaxSlotsD\)/s; exit 1' "$(list_cpp_files | tr '\0' '\n' | grep 'WhitelistManager\.cpp' | head -1)"; then
    fail "CHECK 93 – WhitelistManager max_slots load can still truncate fractional values" \
        "Fix: require FMath::Fmod(MaxSlotsD, 1.0) == 0.0 before static_cast<int32>(MaxSlotsD)."
fi

pass "CHECK 93 done"
echo


# =============================================================================
# CHECK 94: queued WebSocket sends re-check connection state under QueueMutex
# =============================================================================
echo "--- CHECK 94: queued WebSocket sends re-check connection state under lock ---"

WSCLIENT_CPP_CHECK94="$(list_cpp_files | tr '\0' '\n' | grep 'SMLWebSocketClient\.cpp' | head -1)"
if [[ -z "$WSCLIENT_CPP_CHECK94" ]]; then
    fail "CHECK 94 – SMLWebSocketClient.cpp not found"
else
    if ! perl -0777 -ne 'exit 0 if /void\s+USMLWebSocketClient::SendText\s*\(const FString& Message\)\s*\{[\s\S]*?FScopeLock Lock\(&QueueMutex\);[\s\S]*?if \(bIsConnected && Runnable\.IsValid\(\)\)[\s\S]*?EnqueueText\(Message\)[\s\S]*?return;[\s\S]*?PendingSendQueue\.Add\(Message\)/s; exit 1' "$WSCLIENT_CPP_CHECK94"; then
        fail "CHECK 94 – SendText can still strand a queued message during reconnect" \
            "Fix: after taking QueueMutex, re-check bIsConnected/Runnable and send immediately before falling back to PendingSendQueue."
    fi
    if ! perl -0777 -ne 'exit 0 if /void\s+USMLWebSocketClient::SendBinary\s*\(const TArray<uint8>& Data\)\s*\{[\s\S]*?FScopeLock Lock\(&QueueMutex\);[\s\S]*?if \(bIsConnected && Runnable\.IsValid\(\)\)[\s\S]*?EnqueueBinary\(Data\)[\s\S]*?return;[\s\S]*?PendingSendBinaryQueue\.Add\(Data\)/s; exit 1' "$WSCLIENT_CPP_CHECK94"; then
        fail "CHECK 94 – SendBinary(const&) can still strand a queued payload during reconnect" \
            "Fix: after taking QueueMutex, re-check bIsConnected/Runnable and send immediately before falling back to PendingSendBinaryQueue."
    fi
    if ! perl -0777 -ne 'exit 0 if /void\s+USMLWebSocketClient::SendBinary\s*\(TArray<uint8>&& Data\)\s*\{[\s\S]*?FScopeLock Lock\(&QueueMutex\);[\s\S]*?if \(bIsConnected && Runnable\.IsValid\(\)\)[\s\S]*?EnqueueBinary\(Data\)[\s\S]*?return;[\s\S]*?PendingSendBinaryQueue\.Add\(MoveTemp\(Data\)\)/s; exit 1' "$WSCLIENT_CPP_CHECK94"; then
        fail "CHECK 94 – SendBinary(&&) can still strand a queued payload during reconnect" \
            "Fix: after taking QueueMutex, re-check bIsConnected/Runnable and send immediately before falling back to PendingSendBinaryQueue."
    fi
fi

pass "CHECK 94 done"
echo


# =============================================================================
# CHECK 95: PATCH /bans/:uid rejects non-finite durationMinutes values
# =============================================================================
echo "--- CHECK 95: PATCH /bans rejects non-finite durationMinutes values ---"

BANREST_CPP_CHECK95="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
if [[ -z "$BANREST_CPP_CHECK95" ]]; then
    fail "CHECK 95 – BanRestApi.cpp not found"
else
    if ! grep -qP 'if\s*\(bHasDuration\s*&&\s*\(!FMath::IsFinite\(DurationMinutesDbl\)\s*\|\|\s*DurationMinutesDbl\s*<\s*0\.0\)\)' "$BANREST_CPP_CHECK95"; then
        fail "CHECK 95 – PATCH /bans still accepts NaN/Inf durationMinutes" \
            "Fix: reject !FMath::IsFinite(DurationMinutesDbl) before the negative-duration check."
    fi
fi

pass "CHECK 95 done"
echo


# =============================================================================
# CHECK 96: POST /warnings validates parsed uid before auto-ban escalation
# =============================================================================
echo "--- CHECK 96: POST /warnings validates and normalizes uid before auto-ban ---"

BANREST_CPP_CHECK96="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
if [[ -z "$BANREST_CPP_CHECK96" ]]; then
    fail "CHECK 96 – BanRestApi.cpp not found"
else
    if ! grep -q 'UBanDatabase::ParseUid(Uid, WarnPlatform, WarnPlayerUID);' "$BANREST_CPP_CHECK96"; then
        fail "CHECK 96 – POST /warnings does not parse uid into platform/raw id before auto-ban" \
            "Fix: call UBanDatabase::ParseUid(Uid, WarnPlatform, WarnPlayerUID) before warning creation/auto-ban."
    fi
    if ! grep -q 'WarnPlatform == TEXT("UNKNOWN")' "$BANREST_CPP_CHECK96"; then
        fail "CHECK 96 – POST /warnings still accepts uid values without a platform prefix" \
            "Fix: reject UNKNOWN-parsed UIDs instead of creating unmatched auto-bans."
    fi
    if ! grep -q 'BanJson::ValidateUidParts(WarnPlatform, WarnPlayerUID, UidValidationError)' "$BANREST_CPP_CHECK96"; then
        fail "CHECK 96 – POST /warnings missing uid validation before auto-ban" \
            "Fix: validate parsed uid parts (including EOS PUID format) before continuing."
    fi
    if ! grep -q 'Uid = UBanDatabase::MakeUid(WarnPlatform, WarnPlayerUID);' "$BANREST_CPP_CHECK96"; then
        fail "CHECK 96 – POST /warnings does not rebuild the normalized uid before storing warning/ban data" \
            "Fix: rebuild Uid from the validated platform/raw id so EOS ids are normalized consistently."
    fi
fi

pass "CHECK 96 done"
echo


# =============================================================================
# CHECK 97: GeoIP HTTP response lambda wraps KickConnectedPlayer in AsyncTask
# =============================================================================
echo "--- CHECK 97: GeoIP HTTP callback dispatches to game thread via AsyncTask ---"

BANENFORCER_CPP_CHECK97="$(list_cpp_files | tr '\0' '\n' | grep 'BanEnforcer\.cpp' | head -1)"
if [[ -z "$BANENFORCER_CPP_CHECK97" ]]; then
    fail "CHECK 97 – BanEnforcer.cpp not found"
else
    # The HTTP response lambda must dispatch through AsyncTask(ENamedThreads::GameThread,...) 
    # before calling KickConnectedPlayer.
    if ! grep -qP 'AsyncTask\s*\(\s*ENamedThreads::GameThread' "$BANENFORCER_CPP_CHECK97"; then
        fail "CHECK 97 – GeoIP HTTP callback calls KickConnectedPlayer directly off the game thread" \
            "Fix: wrap KickConnectedPlayer and NotifyGeoIpBlocked in AsyncTask(ENamedThreads::GameThread, ...)."
    fi
fi

pass "CHECK 97 done"
echo


# =============================================================================
# CHECK 98: SMLWebSocketServerRunnable token check uses 256-minimum constant-time loop
# =============================================================================
echo "--- CHECK 98: WS server token comparison uses 256-minimum constant-time loop ---"

WSSRVRUNNABLE_CPP_CHECK98="$(list_cpp_files | tr '\0' '\n' | grep 'SMLWebSocketServerRunnable\.cpp' | head -1)"
if [[ -z "$WSSRVRUNNABLE_CPP_CHECK98" ]]; then
    fail "CHECK 98 – SMLWebSocketServerRunnable.cpp not found"
else
    if ! grep -qP 'FMath::Max\s*\(\s*FMath::Max\s*\(\s*AuthLen\s*,\s*ExpectedLen\s*\)\s*,\s*256\s*\)' "$WSSRVRUNNABLE_CPP_CHECK98"; then
        fail "CHECK 98 – WS server token comparison iterates only min(AuthLen,ExpectedLen) bytes, leaking length via timing" \
            "Fix: use N = FMath::Max(FMath::Max(AuthLen, ExpectedLen), 256) with out-of-bounds byte padding to 0."
    fi
fi

pass "CHECK 98 done"
echo


# =============================================================================
# CHECK 99: CSV export lambdas neutralise formula-injection prefixes
# =============================================================================
echo "--- CHECK 99: CSV export neutralises formula-injection prefixes (=, +, -, @) ---"

BANREST_CPP_CHECK99="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
if [[ -z "$BANREST_CPP_CHECK99" ]]; then
    fail "CHECK 99 – BanRestApi.cpp not found"
else
    if ! grep -qP "TEXT\(\"'\"\)" "$BANREST_CPP_CHECK99"; then
        fail "CHECK 99 – CSV export lambdas do not prefix formula-injection chars with a single-quote" \
            "Fix: in every CsvQuote/CsvQ lambda, if the field starts with =, +, -, or @ prepend a single-quote."
    fi
fi

pass "CHECK 99 done"
echo


# =============================================================================
# CHECK 100: POST /bans/backup returns filename only, not full filesystem path
# =============================================================================
echo "--- CHECK 100: POST /bans/backup response contains filename, not full path ---"

BANREST_CPP_CHECK100="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
if [[ -z "$BANREST_CPP_CHECK100" ]]; then
    fail "CHECK 100 – BanRestApi.cpp not found"
else
    # Must NOT return the full path field
    if grep -qP '"path"\s*,\s*Dest' "$BANREST_CPP_CHECK100"; then
        fail "CHECK 100 – backup endpoint still returns full filesystem path in 'path' field" \
            "Fix: return only FPaths::GetCleanFilename(Dest) in a 'filename' field."
    fi
    # Must return the clean filename
    if ! grep -qP 'FPaths::GetCleanFilename\s*\(\s*Dest\s*\)' "$BANREST_CPP_CHECK100"; then
        fail "CHECK 100 – backup endpoint does not use FPaths::GetCleanFilename to strip the path" \
            "Fix: Obj->SetStringField(TEXT(\"filename\"), FPaths::GetCleanFilename(Dest))."
    fi
fi

pass "CHECK 100 done"
echo


# =============================================================================
# CHECK 101: ValidateUidParts writes back normalised strings only on success
# =============================================================================
echo "--- CHECK 101: ValidateUidParts does not mutate caller args on failure ---"

BANREST_CPP_CHECK101="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
if [[ -z "$BANREST_CPP_CHECK101" ]]; then
    fail "CHECK 101 – BanRestApi.cpp not found"
else
    # Must use local copies P / U and write back at the end
    if ! perl -0777 -ne 'exit 0 if /static bool ValidateUidParts.*?\{.*?FString P = Platform\.ToUpper\(\);.*?FString U = PlayerUID;.*?Platform\s+=\s+P;.*?PlayerUID\s+=\s+U;.*?return true;/s; exit 1' "$BANREST_CPP_CHECK101"; then
        fail "CHECK 101 – ValidateUidParts still mutates Platform/PlayerUID before validation completes" \
            "Fix: work on local copies P/U; write back to Platform/PlayerUID only after all validation passes."
    fi
fi

pass "CHECK 101 done"
echo


# =============================================================================
# CHECK 102: Persisted nextId=0 is rejected and reset to 1 with a warning
# =============================================================================
echo "--- CHECK 102: persisted nextId=0 triggers warning + reset in all 3 registries ---"

BANDB_CPP_CHECK102="$(list_cpp_files | tr '\0' '\n' | grep 'BanDatabase\.cpp' | head -1)"
BANAUDIT_CPP_CHECK102="$(list_cpp_files | tr '\0' '\n' | grep 'BanAuditLog\.cpp' | head -1)"
BANAPPEAL_CPP_CHECK102="$(list_cpp_files | tr '\0' '\n' | grep 'BanAppealRegistry\.cpp' | head -1)"
if [[ -z "$BANDB_CPP_CHECK102" || -z "$BANAUDIT_CPP_CHECK102" || -z "$BANAPPEAL_CPP_CHECK102" ]]; then
    fail "CHECK 102 – one or more registry cpp files not found"
else
    for F in "$BANDB_CPP_CHECK102" "$BANAUDIT_CPP_CHECK102" "$BANAPPEAL_CPP_CHECK102"; do
        if ! grep -qP 'persisted nextId=0 is invalid' "$F"; then
            fail "CHECK 102 – $F does not warn and reset on persisted nextId=0" \
                "Fix: if loaded nextId is 0, log Warning and reset to 1 (scan from existing entries)."
        fi
    done
fi

pass "CHECK 102 done"
echo


# =============================================================================
# CHECK 103: Scheduled ban drop writes an audit log entry
# =============================================================================
echo "--- CHECK 103: scheduled ban drop writes an audit log entry ---"

SCHEDBAN_CPP_CHECK103="$(list_cpp_files | tr '\0' '\n' | grep 'ScheduledBanRegistry\.cpp' | head -1)"
if [[ -z "$SCHEDBAN_CPP_CHECK103" ]]; then
    fail "CHECK 103 – ScheduledBanRegistry.cpp not found"
else
    if ! grep -qP 'scheduled_ban_dropped' "$SCHEDBAN_CPP_CHECK103"; then
        fail "CHECK 103 – scheduled ban drop (RetryCount >= 5) does not write an audit log entry" \
            "Fix: call AuditLog->LogAction(TEXT(\"scheduled_ban_dropped\"), ...) when dropping a retried entry."
    fi
fi

pass "CHECK 103 done"
echo


# =============================================================================
# CHECK 104: Backup filename uses atomic counter to disambiguate same-second calls
# =============================================================================
echo "--- CHECK 104: Backup() uses atomic counter to avoid same-second filename collision ---"

BANDB_CPP_CHECK104="$(list_cpp_files | tr '\0' '\n' | grep 'BanDatabase\.cpp' | head -1)"
if [[ -z "$BANDB_CPP_CHECK104" ]]; then
    fail "CHECK 104 – BanDatabase.cpp not found"
else
    if ! grep -qP 'std::atomic<uint32>\s+BackupSeq' "$BANDB_CPP_CHECK104"; then
        fail "CHECK 104 – Backup() does not use an atomic counter to disambiguate same-second filenames" \
            "Fix: add static std::atomic<uint32> BackupSeq{0} and append its value (mod 1000) to the timestamp."
    fi
fi

pass "CHECK 104 done"
echo


# =============================================================================
# CHECK 105: IsValidEOSPUID rejects uppercase hex digits
# =============================================================================
echo "--- CHECK 105: IsValidEOSPUID rejects uppercase hex digits ---"

BANCHAT_CPP_CHECK105="$(list_cpp_files | tr '\0' '\n' | grep 'BanChatCommands\.cpp' | head -1)"
if [[ -z "$BANCHAT_CPP_CHECK105" ]]; then
    fail "CHECK 105 – BanChatCommands.cpp not found"
else
    if grep -qF "FChar::IsHexDigit" "$BANCHAT_CPP_CHECK105"; then
        fail "CHECK 105 – IsValidEOSPUID still uses FChar::IsHexDigit which accepts uppercase A-F" \
            "Fix: replace with explicit (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') to reject uppercase."
    fi
    if ! grep -qP "c >= TEXT\('a'\) && c <= TEXT\('f'\)" "$BANCHAT_CPP_CHECK105"; then
        fail "CHECK 105 – IsValidEOSPUID does not explicitly check lowercase a-f only" \
            "Fix: use (c >= TEXT('0') && c <= TEXT('9')) || (c >= TEXT('a') && c <= TEXT('f'))."
    fi
fi

pass "CHECK 105 done"
echo


# =============================================================================
# CHECK 106: bVerifyWSCertificate config option is threaded through BanSyncClient
# =============================================================================
echo "--- CHECK 106: bVerifyWSCertificate config option threaded through BanSyncClient/BanWebSocketPusher ---"

BANSYNC_CPP_CHECK106="$(list_cpp_files | tr '\0' '\n' | grep 'BanSyncClient\.cpp' | head -1)"
BANWSPUSHER_CPP_CHECK106="$(list_cpp_files | tr '\0' '\n' | grep 'BanWebSocketPusher\.cpp' | head -1)"
if [[ -z "$BANSYNC_CPP_CHECK106" || -z "$BANWSPUSHER_CPP_CHECK106" ]]; then
    fail "CHECK 106 – BanSyncClient.cpp or BanWebSocketPusher.cpp not found"
else
    if ! grep -qP 'bVerifySSLCertificate\s*=\s*Cfg->bVerifyWSCertificate' "$BANSYNC_CPP_CHECK106"; then
        fail "CHECK 106 – BanSyncClient does not propagate bVerifyWSCertificate to the WS client" \
            "Fix: Client->bVerifySSLCertificate = Cfg->bVerifyWSCertificate; before Connect()."
    fi
    if ! grep -qP 'bVerifySSLCertificate\s*=\s*Cfg->bVerifyWSCertificate' "$BANWSPUSHER_CPP_CHECK106"; then
        fail "CHECK 106 – BanWebSocketPusher does not propagate bVerifyWSCertificate to the WS client" \
            "Fix: Client->bVerifySSLCertificate = Cfg->bVerifyWSCertificate; before Connect()."
    fi
fi

pass "CHECK 106 done"
echo


# =============================================================================
# CHECK 107: durationMinutes parsers reject non-integer positive JSON numbers
# =============================================================================
echo "--- CHECK 107: durationMinutes rejects fractional positive values (no truncation) ---"

BANREST_CPP_CHECK107="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
BANSYNC_CPP_CHECK107="$(list_cpp_files | tr '\0' '\n' | grep 'BanSyncClient\.cpp' | head -1)"
if [[ -z "$BANREST_CPP_CHECK107" || -z "$BANSYNC_CPP_CHECK107" ]]; then
    fail "CHECK 107 – BanRestApi.cpp or BanSyncClient.cpp not found"
else
    # POST /bans, POST /bans/ip, POST /scheduled, POST /bans/bulk should all
    # reject non-integer positive durationMinutes values instead of truncating.
    int_msg_count=$(grep -cF 'durationMinutes must be an integer number of minutes' "$BANREST_CPP_CHECK107")
    if [[ "$int_msg_count" -lt 4 ]]; then
        fail "CHECK 107 – BanRestApi durationMinutes routes do not consistently reject fractional positive values" \
            "Fix: for each route that reads durationMinutes, if value is finite and >0, require FMath::Fmod(value,1.0)==0.0 or return 400."
    fi
    if ! grep -qP 'FMath::Fmod\(DurDbl,\s*1\.0\)\s*!=\s*0\.0' "$BANSYNC_CPP_CHECK107"; then
        fail "CHECK 107 – BanSyncClient peer durationMinutes parse can still truncate fractional values" \
            "Fix: reject/drop peer ban messages when durationMinutes is finite, >0, and non-integer."
    fi
fi

pass "CHECK 107 done"
echo


# =============================================================================
# CHECK 108: GeoIP AsyncTask — all UObject ops are inside the game-thread task
# =============================================================================
echo "--- CHECK 108: GeoIP AsyncTask boundary — no UObject ops before AsyncTask on HTTP thread ---"

BANENFORCER_CPP_CHECK108="$(list_cpp_files | tr '\0' '\n' | grep 'BanEnforcer\.cpp' | head -1)"
if [[ -z "$BANENFORCER_CPP_CHECK108" ]]; then
    fail "CHECK 108 – BanEnforcer.cpp not found"
else
    # The old bug was calling WeakPC.Get() / IsValid / GetWorld() BEFORE AsyncTask
    # on the HTTP thread.  After the fix those calls are inside the AsyncTask lambda.
    # We verify by checking that the file no longer contains the pre-task raw-pointer
    # pattern: "PCKick = WeakPC.Get();" followed within a few lines by "W2 = PCKick->GetWorld()"
    # outside of a lambda body (i.e., as a plain statement).
    # Simpler mechanical proxy: the two lines "APlayerController* PCKick = WeakPC.Get();"
    # and "UWorld* W2 = PCKick->GetWorld();" should only appear INSIDE AsyncTask lambdas,
    # never as bare statements before "AsyncTask(" in the same callback scope.
    # We enforce this by counting occurrences of "PCKick = WeakPC.Get();" — they must
    # ALL appear after (i.e., deeper indentation than) "AsyncTask(ENamedThreads::GameThread".
    # The simplest scriptable check: no occurrence of
    #   "APlayerController* PCKick = WeakPC.Get();"
    # should appear in a line that is NOT inside a lambda (i.e., not preceded by "{" on the same
    # or immediately preceding AsyncTask line). We approximate this by verifying that every
    # occurrence of "PCKick = WeakPC.Get()" is preceded within 3 lines by "GameThread".
    while IFS= read -r lineno; do
        # Get the surrounding context (3 lines before)
        context=$(awk "NR>=$((lineno-3)) && NR<$lineno" "$BANENFORCER_CPP_CHECK108")
        if ! echo "$context" | grep -qF "GameThread"; then
            fail "CHECK 108 – BanEnforcer.cpp line $lineno: WeakPC.Get() called outside AsyncTask(GameThread) lambda" \
                "Fix: move WeakPC.Get(), IsValid(), and GetWorld() inside the AsyncTask body."
        fi
    done < <(grep -n 'PCKick = WeakPC\.Get()' "$BANENFORCER_CPP_CHECK108" | cut -d: -f1)
fi

pass "CHECK 108 done"
echo


# =============================================================================
# CHECK 109: POST /bans and POST /bans/ip reject durationMinutes <= 0 explicitly
# =============================================================================
echo "--- CHECK 109: POST /bans and POST /bans/ip reject durationMinutes <= 0 with a 400 error ---"

BANREST_CPP_CHECK109="$(list_cpp_files | tr '\0' '\n' | grep 'BanRestApi\.cpp' | head -1)"
if [[ -z "$BANREST_CPP_CHECK109" ]]; then
    fail "CHECK 109 – BanRestApi.cpp not found"
else
    reject_count=$(grep -cF 'durationMinutes must be a positive integer; omit the field for a permanent ban' "$BANREST_CPP_CHECK109")
    if [[ "$reject_count" -lt 2 ]]; then
        fail "CHECK 109 – BanRestApi POST /bans and/or POST /bans/ip do not explicitly reject durationMinutes <= 0" \
            "Fix: before the int32 cast, check 'if (bHasDurationMinutes && (<= 0 || !IsFinite))' and return 400."
    fi
fi

pass "CHECK 109 done"
echo
if [[ "$ISSUES" -eq 0 ]]; then
    echo -e "${GRN}All checks passed — no issues found.${NC}"
    exit 0
else
    echo -e "${RED}${ISSUES} issue(s) found. Review the FAIL entries above.${NC}"
    exit 1
fi
