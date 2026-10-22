# MONOLITH EDITORIAL — Design System (`DESIGN.md`)

- **Design System Name:** Monolith Editorial
- **Design Style:** Monochrome Editorial Minimalism *(Swiss-Inspired Technical Minimalism)*
- **Reference Inspiration:** [benjdd.com](https://benjdd.com/)

---

## 1. Overview & Design Style Classification

The visual language of [benjdd.com](https://benjdd.com/) belongs to **Monochrome Editorial Minimalism** (often referred to as **Swiss-Inspired Technical Minimalism**):
- **Monochrome / Achromatic Palette:** Zero decorative hues; hierarchy is achieved strictly through luminance contrast—warm matte charcoal (`#1e1e1e`), pure black surfaces (`#000000`), mid-tone neutral borders (`#646464`), and soft off-white typography (`#f0f0f0`) in dark mode, with an inverted high-craft light paper mode (`#e0e0e0` / `#141414`).
- **Editorial Single-Column Rhythm:** A focused reading measure (`48rem` / `768px`) where content flows vertically with generous whitespace and hairline horizontal rules rather than heavy cards or multi-column grids.
- **Technical-Humanist Typography Pairing:** Light-weight geometric sans-serif prose (`Figtree`, weight `300`) paired with crisp, utilitarian monospace (`IBM Plex Mono`) for code tokens, credentials, and `.ino` file download triggers.

---

## 2. Color Tokens (CSS Custom Properties)

Colors are defined as RGB triplets so they can be composed with alpha channels (`rgba(var(--color-*), <alpha>)`):

### Dark Theme (Default: `html[data-theme="dark"]`)
| Token | RGB Value | Hex Equivalent | Usage |
| :--- | :--- | :--- | :--- |
| `--color-fill` | `30, 30, 30` | `#1e1e1e` | Primary page background |
| `--color-text-base` | `240, 240, 240` | `#f0f0f0` | Primary body & heading text |
| `--color-accent` | `240, 240, 240` | `#f0f0f0` | Interactive hover states, focus outlines, active icons |
| `--color-card` | `0, 0, 0` | `#000000` | Code badges, button surfaces, scrollbar thumb |
| `--color-card-muted` | `80, 80, 80` | `#505050` | Button hover surfaces, scrollbar hover |
| `--color-border` | `100, 100, 100` | `#646464` | Subtle dividers, card & button borders |

### Light Theme (`html[data-theme="light"]`)
| Token | RGB Value | Hex Equivalent | Usage |
| :--- | :--- | :--- | :--- |
| `--color-fill` | `224, 224, 224` | `#e0e0e0` | Primary page background |
| `--color-text-base` | `20, 20, 20` | `#141414` | Primary body & heading text |
| `--color-accent` | `100, 100, 100` | `#646464` | Interactive hover states, focus outlines |
| `--color-card` | `190, 190, 190` | `#bebebe` | Code badges, button surfaces |
| `--color-card-muted` | `205, 205, 205` | `#cdcdcd` | Button hover surfaces |
| `--color-border` | `200, 200, 200` | `#c8c8c8` | Subtle dividers, card & button borders |

---

## 3. Typography

### Font Families (Google Fonts)
- **Sans-Serif (Body & Headings):** `'Figtree', 'Raleway', 'Poppins', 'Inter', Arial, sans-serif`
- **Monospace (Code, Credentials & `.ino` Buttons):** `'IBM Plex Mono', monospace`

### Scale & Weights
- **Body:** `font-size: 1.125rem` (`18px`), `line-height: 1.75rem` (`28px`), `font-weight: 300`
- **Top Header Title (`IOT Experiments`):** `font-size: 2.25rem` (`36px`), `line-height: 2.5rem` (`40px`), `font-weight: 500` on desktop (`1.75rem` on mobile)
- **Section Heading (`h2`):** `font-size: 1.5rem` (`24px`), `line-height: 2rem` (`32px`), `font-weight: 500`, `letter-spacing: 0.025em`
- **Experiment Label:** `font-size: 1.075rem`, `line-height: 1.75rem`, `font-weight: 300`, `white-space: pre-line`
- **Download Button (`button.ino-btn`):** `font-family: 'IBM Plex Mono', monospace`, `font-size: 0.9rem`, `font-weight: 500`

---

## 4. Layout & Spacing
- **Page Container (`header`, `main`, `footer`):** Centered column with `max-width: 48rem` (`768px`), `margin: 0 auto`, `padding: 0 1rem`.
- **Full-Viewport Structure:** `min-height: 100svh`, `display: flex`, `flex-direction: column` with `footer` pushed to the bottom via `margin-top: auto`.
- **Header Navigation (`.top-nav-wrap`):** Flex row (`justify-content: space-between; align-items: center; padding: 2rem 0 1.5rem`), containing the **IOT Experiments** title and a sun/moon theme toggle button.
- **Experiment List Items (`.experiment-item`):** Vertical rhythm of `padding: 1.75rem 0` separated by `1px solid rgba(var(--color-border), 0.35)` horizontal dividers, keeping the page airy and scannable.

---

## 5. Micro-Interactions & Details
- **Text Selection:** `background-color: rgba(var(--color-accent), 0.7); color: rgb(var(--color-fill))`
- **Custom Scrollbar:** `0.75rem` width, track in `rgb(var(--color-fill))`, thumb in `rgb(var(--color-card))`, hover in `rgb(var(--color-card-muted))`.
- **Focus Outlines:** `2px dashed rgb(var(--color-accent))` with `2px` offset.
- **Download Button Hover:** Background shifts from `rgba(var(--color-card), 0.75)` to `rgba(var(--color-card-muted), 0.45)`, border brightens to `rgb(var(--color-accent))`, and button lifts `-1px`.
- **Theme Toggle Button:** Subtle `12deg` rotation on hover.
