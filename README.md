# ECE445 FA25 Project: Auto-Adjusted Smart Lighting System for Healthy Indoor Environments

Team 15: zl114, kdchen2, jihyun4

# Introduction:

Prolonged desk work under poor lighting can lead to eye strain, headaches, and fatigue. Most desk lamps are static, requiring manual adjustment and offering no adaptation to daylight changes or different tasks. A smart desk lamp that dynamically controls both brightness and color temperature could provide healthier, more comfortable lighting.

Our solution is a smart desk lamp with sensors and a controller that automatically adjusts both illuminance (lux level) and color temperature.

# Code:

Latest firmware is uploaded under /code/. See /notebooks/kdchen2 for prior versions of firmware.

# Results:

The Auto-Adjusted Smart Desk Lamp successfully met its primary high-level requirements. We engineered a dual-rail power system that efficiently steps down 12 V to 3.3 V, allowing the integration of high-power LED strips with sensitive logic-level control. The final device successfully maintains a target desk brightness of approximately 450 lux with an error margin of less than 10%, regardless of ambient lighting conditions.

Furthermore, the power efficiency goal was exceeded. The system demonstrated a 35.2% reduction in power consumption when shifting from dark to daylight modes, surpassing the 20% requirement. The control algorithm, utilizing a moving-average filter and gamma correction, proved capable of adjusting brightness at a rate of less than 2% per second, ensuring a flicker-free user experience that minimizes eye strain.


