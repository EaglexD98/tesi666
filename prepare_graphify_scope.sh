#!/usr/bin/env bash
set -euo pipefail

PROJECT="/home/eagle/tesi666"

# Original clean frameworks
ORIG_INET="/home/eagle/inet-4.5.4"
ORIG_SIMU5G="/home/eagle/simu5g-1.4.1"

# Modified frameworks inside your project
MOD_INET="/home/eagle/tesi666/inet"
MOD_SIMU5G="/home/eagle/tesi666/simu5G"

SCOPE="$PROJECT/graphify_scope"

echo "== Checking folders =="

for d in "$PROJECT" "$ORIG_INET" "$ORIG_SIMU5G" "$MOD_INET" "$MOD_SIMU5G"; do
    if [ ! -d "$d" ]; then
        echo "ERROR: folder not found: $d"
        exit 1
    fi
    echo "OK: $d"
done

cd "$PROJECT"

echo
echo "== Detecting modified Simu5G files =="

find "$MOD_SIMU5G" -type f \( \
    -name "*.cc" -o -name "*.cpp" -o -name "*.c" -o \
    -name "*.h" -o -name "*.hpp" -o -name "*.hh" -o \
    -name "*.ned" -o -name "*.ini" -o -name "*.msg" -o \
    -name "*.xml" -o -name "*.md" -o -name "*.txt" \
\) \
-not -path "*/.git/*" \
-not -path "*/out/*" \
-not -path "*/build/*" \
-not -path "*/results/*" \
-not -path "*/.oppbuild/*" \
-not -path "*/debug/*" \
-not -path "*/release/*" \
| while IFS= read -r f; do
    rel="${f#$MOD_SIMU5G/}"
    orig="$ORIG_SIMU5G/$rel"

    if [ ! -f "$orig" ] || ! cmp -s "$f" "$orig"; then
        printf '%s\n' "$rel"
    fi
done | sort > changed_simu5g_rel.txt

echo "Modified Simu5G files:"
wc -l changed_simu5g_rel.txt

echo
echo "== Detecting modified INET files =="

find "$MOD_INET" -type f \( \
    -name "*.cc" -o -name "*.cpp" -o -name "*.c" -o \
    -name "*.h" -o -name "*.hpp" -o -name "*.hh" -o \
    -name "*.ned" -o -name "*.ini" -o -name "*.msg" -o \
    -name "*.xml" -o -name "*.md" -o -name "*.txt" \
\) \
-not -path "*/.git/*" \
-not -path "*/out/*" \
-not -path "*/build/*" \
-not -path "*/results/*" \
-not -path "*/.oppbuild/*" \
-not -path "*/debug/*" \
-not -path "*/release/*" \
| while IFS= read -r f; do
    rel="${f#$MOD_INET/}"
    orig="$ORIG_INET/$rel"

    if [ ! -f "$orig" ] || ! cmp -s "$f" "$orig"; then
        printf '%s\n' "$rel"
    fi
done | sort > changed_inet_rel.txt

echo "Modified INET files:"
wc -l changed_inet_rel.txt

echo
echo "== Creating project-relative file lists =="

sed 's#^#simu5G/#' changed_simu5g_rel.txt > changed_simu5g_project.txt
sed 's#^#inet/#' changed_inet_rel.txt > changed_inet_project.txt
cat changed_simu5g_project.txt changed_inet_project.txt > changed_framework_files.txt

echo "Total modified framework files:"
wc -l changed_framework_files.txt

echo
echo "== Rebuilding graphify_scope =="

rm -rf "$SCOPE"
mkdir -p "$SCOPE"

copy_selected_dir() {
    local srcdir="$1"
    local dstdir="$2"

    if [ -d "$srcdir" ]; then
        mkdir -p "$dstdir"
        rsync -a --prune-empty-dirs \
            --include='*/' \
            --include='*.cc' \
            --include='*.cpp' \
            --include='*.c' \
            --include='*.h' \
            --include='*.hpp' \
            --include='*.hh' \
            --include='*.ned' \
            --include='*.ini' \
            --include='*.msg' \
            --include='*.xml' \
            --include='*.md' \
            --include='*.txt' \
            --exclude='*' \
            --exclude='results/' \
            --exclude='out/' \
            --exclude='build/' \
            --exclude='.oppbuild/' \
            --exclude='debug/' \
            --exclude='release/' \
            "$srcdir/" "$dstdir/"
    fi
}

# Copy your own project folders, not the full external frameworks
copy_selected_dir "$PROJECT/src" "$SCOPE/src"
copy_selected_dir "$PROJECT/simulations" "$SCOPE/simulations"
copy_selected_dir "$PROJECT/veins_inet" "$SCOPE/veins_inet"

# Copy useful root files
find "$PROJECT" -maxdepth 1 -type f \( \
    -name "*.cc" -o -name "*.cpp" -o -name "*.c" -o \
    -name "*.h" -o -name "*.hpp" -o -name "*.hh" -o \
    -name "*.ned" -o -name "*.ini" -o -name "*.msg" -o \
    -name "*.xml" -o -name "*.md" -o -name "*.txt" \
\) -exec cp -a {} "$SCOPE/" \;

# Copy only modified INET/Simu5G files
while IFS= read -r relpath; do
    [ -z "$relpath" ] && continue
    src="$PROJECT/$relpath"
    dst="$SCOPE/$relpath"

    if [ -f "$src" ]; then
        mkdir -p "$(dirname "$dst")"
        cp -a "$src" "$dst"
    else
        echo "WARNING: listed file not found: $src"
    fi
done < changed_framework_files.txt

echo
echo "== Creating MODIFIED_FRAMEWORK_FILES.md =="

{
    echo "# Modified Framework Files"
    echo
    echo "This folder contains a reduced Graphify scope for the OMNeT++ project."
    echo
    echo "It includes:"
    echo "- Custom project files from src/, simulations/, and veins_inet/."
    echo "- Only modified files detected in INET and Simu5G."
    echo "- No full external framework copy."
    echo
    echo "## Modified Simu5G files"
    if [ -s changed_simu5g_rel.txt ]; then
        sed 's#^#- simu5G/#' changed_simu5g_rel.txt
    else
        echo "- None detected"
    fi
    echo
    echo "## Modified INET files"
    if [ -s changed_inet_rel.txt ]; then
        sed 's#^#- inet/#' changed_inet_rel.txt
    else
        echo "- None detected"
    fi
} > "$SCOPE/MODIFIED_FRAMEWORK_FILES.md"

cat > "$SCOPE/.graphifyignore" <<'IGNORE'
# Ignore generated outputs
results/
out/
build/
.oppbuild/
debug/
release/

# Ignore simulation output files
*.sca
*.vec
*.vci
*.elog
*.anf
*.stat
*.csv

# Ignore binaries and compiled files
*.o
*.so
*.a
*.exe
*.dll
*.class

# Ignore logs and temporary files
*.log
*.tmp
*.bak
*~

# Ignore images to avoid unnecessary semantic analysis
*.png
*.jpg
*.jpeg
*.gif
*.svg
*.webp
IGNORE

echo
echo "== Summary =="
echo "Changed Simu5G files: $(wc -l < changed_simu5g_rel.txt)"
echo "Changed INET files:   $(wc -l < changed_inet_rel.txt)"
echo "Scope files total:    $(find "$SCOPE" -type f | wc -l)"
echo
echo "First modified Simu5G files:"
head -20 changed_simu5g_rel.txt || true
echo
echo "First modified INET files:"
head -20 changed_inet_rel.txt || true
echo
echo "Graphify scope created at:"
echo "$SCOPE"
echo
echo "Next command when Gemini quota is available:"
echo "graphify extract graphify_scope --backend gemini --force"
