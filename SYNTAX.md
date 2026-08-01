# Directive Regular Language Specification

This document outlines a regular language designed for structured thought organization and information parsing. It uses strict directive keywords to establish relationships, definitions, and logical flows.

## Core Parsing Rules

1. **Syntax Markers**: All directives begin with a period (`.`) immediately followed by the keyword (e.g., `.define`). 
2. **Argument Boundaries**: Parsing is done inline using keywords and newlines. 
   - The first argument is the text between the initial keyword and the next keyword.
   - Subsequent arguments are bounded by keywords.
   - The final argument is bounded by the preceding keyword and captures all subsequent text (including newlines and lists) until the next directive (a line starting with a `.`) or the end of the file.
3. **Formatting Independence**: Markdown formatting (such as `**bolding**` or `*italics*`) is ignored by the parser. Only the raw text and the period-prefixed keywords dictate structure.

---

## 1. Ontology & Definitions

These directives are used to build a knowledge graph, establish definitions, and declare compositional relationships between entities.

### `.define`
Creates a formal definition or alias for a concept.
- **Syntax**: `.define [Concept] as [Definition]`
- **Example**: 
  `.define Regular Expression as A sequence of characters that specifies a search pattern.`

### `.type`
Establishes a class inheritance or hierarchical categorization for an entity.
- **Syntax**: `.type [Entity] is [Category]`
- **Example**: 
  `.type The Solar System is a Planetary System.`

### `.set`
Declares a compositional relationship, possession, or a property of an entity.
- **Syntax**: `.set [Entity] has [Constituents]`
- **Example**: 
  `.set The Solar System has
    - Mercury
    - Venus
    - Earth
    - Mars
    - ...`

### `.sequence`
Declares a chronological order, process, or an ordered list of elements for an entity or event.
- **Syntax**: `.sequence [Process/Entity] has [Ordered Elements]`
- **Example**: 
  `.sequence The scientific method has
    1. Observation
    2. Hypothesis
    3. Experimentation
    4. Analysis
    5. Conclusion`

### `.relate`
Establishes a specific, directional relationship between two distinct entities.
- **Syntax**: `.relate [Entity A] to [Entity B] by [Relationship Context]`
- **Example**: 
  `.relate User to System by Authenticated Sessions.`

---

## 2. Logic & Reasoning

These directives are used to construct arguments, establish causality, and define conditional truths.

### `.if`
Declares a conditional dependency or a logical consequence.
- **Syntax**: `.if [Condition] then [Consequence]`
- **Example**: 
  `.if The server is down then The application will fail to load.`

### `.why`
Establishes a causal link or justification for a statement.
- **Syntax**: `.why [Observation/Conclusion] since [Reason/Premise]`
- **Example**: 
  `.why The sky appears blue since Rayleigh scattering disperses short-wavelength light in the atmosphere.`

### `.truth`
Declares an absolute axiom, a verified fact, or a foundational assumption that requires no further justification in the current context.
- **Syntax**: `.truth [Statement]`
- **Example**: 
  `.truth All biological life on Earth requires water.`

### `.refute`
Declares a statement to be false, contradictory, or mutually exclusive, along with the evidence.
- **Syntax**: `.refute [Statement] because [Evidence]`
- **Example**: 
  `.refute The earth is flat because Satellite imagery and gravity demonstrate its spherical shape.`
