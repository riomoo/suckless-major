/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 16;        /* gaps between windows */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int snap      = 2;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]     = {"Mononoki Nerd Font:size=11:antialias=true:autohint=true",
                                  "Hack:size=10:antialias=true:autohint=true",
                                  "JoyPixels:size=12:antialias=true:autohint=true"};

#include "../../../themes/using/colors-wal-dwm.h"
/* tagging */
static const char *tags[] = { "", "", "", "", "", "" };

static const Rule rules[] = {
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "chromium", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "mpv",     NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ "xterm-256color",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "xterm-256color",      NULL,     "pulsemixer",           0,         1,          1,           1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "horizgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",      horizgrid },
	{ "|||",      col },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *web[] = { "qutebrowser", NULL};
static const char *tmux[] = { "st", "-e", "tmux", NULL };
static const char *volume[] = { "st", "-e", "pulsemixer", NULL };
static const char *ran[] = { "st", "-e", "lf", NULL };
static const char *sunlock[] = { "steggy", NULL };
static const char *imgeditor[] = { "gimp", NULL};
static const char *passes[] = { "passmenu", NULL};
static const char *wallpaperchange[] = { "walls", NULL};
static const char *wrgrd[] = { "qwg", NULL};
static const char *tmclip[] = { "tmpclip", NULL};
static const char *dmeclip[] = { "dclip", NULL};
static const char *ytwatch[] = { "ytwatch", NULL};
static const char *ytplay[] = { "ytplaylist", NULL};
static const char *bukudmen[] = { "buku-dmenu", NULL};
static const char *screenshot[] = { "scrotty", NULL};
static const char *newvolp[] = { "changevolume", "up", NULL};
static const char *newvold[] = { "changevolume", "down", NULL};
static const char *newvolm[] = { "changevolume", "mute", NULL};



#include "movestack.c"
static Key keys[] = {
	/* modifier             chain key  key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = web } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -10 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +10 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

   /* Layout manipulation */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    /* Switch to specific layouts */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[4]} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

    /* Switching between monitors */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
    /* Keybindings for programs using the format SUPER + ALT + "key" */
	{ MODKEY|Mod1Mask|ControlMask,              XK_p,      spawn,          {.v = wrgrd } },
	{ MODKEY|Mod1Mask,			    XK_d,      spawn,          {.v = newvold } },
	{ MODKEY|Mod1Mask,			    XK_p,      spawn,          {.v = newvolp } },
	{ MODKEY|Mod1Mask,			    XK_m,      spawn,          {.v = newvolm } },
	{ MODKEY|Mod1Mask|ControlMask,              XK_u,      spawn,          {.v = sunlock } },
	{ MODKEY|Mod1Mask|ControlMask,              XK_c,      spawn,          {.v = tmclip } },
	{ MODKEY|Mod1Mask|ControlMask,              XK_d,      spawn,          {.v = dmeclip } },
	{ MODKEY|Mod1Mask|ControlMask,              XK_y,      spawn,          {.v = ytwatch } },
	{ MODKEY|Mod1Mask|ControlMask,              XK_m,      spawn,          {.v = ytplay } },
	{ MODKEY|Mod1Mask|ControlMask,              XK_n,      spawn,          {.v = ran } },
	{ MODKEY|ControlMask,		            XK_b,      spawn,          {.v = bukudmen } },
	{ MODKEY|Mod1Mask,              XK_t,      spawn,          {.v = tmux } },
	{ MODKEY|Mod1Mask,              XK_v,      spawn,          {.v = volume } },
	{ MODKEY|Mod1Mask,              XK_g,      spawn,          {.v = imgeditor } },
	{ MODKEY|Mod1Mask,              XK_e,      spawn,          {.v = passes } },
	{ MODKEY|Mod1Mask,              XK_c,      spawn,          {.v = screenshot } },
	{ MODKEY|Mod1Mask,              XK_n,      spawn,          {.v = wallpaperchange } },
    /* Doom emacs keybindings ushe keychord CTRL + e followed by "key" */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,	      {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} },
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};
