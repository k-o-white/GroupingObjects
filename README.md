<p>This project reads from .txt file dataset, that describes objects of the form "name, X coordinate, Y coordinate, object type, creation time", groups by user-selected criteria (distance from origin, name, creation time, object type) and writes grouped and sorted data into the output .txt file.</p>
<p>It's recommended to use MSVC compiler to build this project.</p>
<h2>How to build</h2>
<blockquote>
    <code>git clone https://github.com/k-o-white/GroupingObjects.git</code><br>
    <code>cd GroupingObjects</code><br>
    <code>mkdir build</code><br>
    <code>cd build</code><br>
    <code>cmake -G "Visual Studio 17 2012" ..</code> (for example)<br>
    <code>cmake --build . --config Release --target GroupingObjects</code><br>
    <code>cd src</code><br>
    <code>start GroupingObjects.exe</code>
</blockquote>
