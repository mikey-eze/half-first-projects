$fn=64;

// INTENSE SCRAP — translucent CAD-style enclosure
// Spotify display + 3 physical controls, no rotary encoder.

W = 82;
D = 48;
H = 18;
wall = 2.2;

module rounded_box(s, r) {
    hull() {
        for (x=[r,s[0]-r])
            for (y=[r,s[1]-r])
                translate([x,y,0]) cylinder(h=s[2], r=r);
    }
}

module shell() {
    difference() {
        rounded_box([W,D,H], 4);

        // Hollow interior while keeping a light, frosted/translucent shell.
        translate([wall,wall,wall])
            rounded_box([W-2*wall,D-2*wall,H], 2);

        // 1.8" TFT display opening — display is not touchscreen.
        translate([18,8,H-3]) cube([46,24,6]);

        // Three physical music controls: previous / play-pause / next.
        for (x=[20,41,62])
            translate([x,40,H-3]) cylinder(h=6,r=2.8);

        // USB-C side opening.
        translate([W-4,12,7])
            rotate([0,90,0]) cube([6,10,5],center=true);

        // Optional wired-headphone opening.
        translate([4,36,8])
            rotate([0,90,0]) cylinder(h=6,r=3.2);
    }
}

// Simple internal placeholders for CAD preview/assembly context.
// These are intentionally subtle so the shell reads as translucent/frosted.
module electronics_preview() {
    color([0.12,0.12,0.12,0.55])
        translate([9,9,2.8]) cube([22,28,3]);       // ESP32 board
    color([0.05,0.05,0.05,0.65])
        translate([20,8,5.8]) cube([46,24,2]);      // TFT body
    color([0.85,0.85,0.85,0.7])
        translate([9,36,3]) cube([12,8,3]);         // battery area
    color([0.95,0.95,0.95,0.8])
        for (x=[20,41,62])
            translate([x,40,3]) cylinder(h=5,r=2.0); // tactile buttons
}

// Light/frosted appearance for CAD inspection.
color([0.94,0.94,0.94,0.58]) shell();
electronics_preview();
