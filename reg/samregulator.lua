-- regulator PID
function Regulator(uchyb, last_uchyb, last_i)
  print(uchyb)
    local p = Kp * uchyb
    local i = (Kp * 1/Ti * Tp * uchyb) + last_i
    local d = Kp * (uchyb - last_uchyb)/Tp * Td
    local reg = p + i + d
    print(p, string.format("%.2f", i), d)
    if reg > Limit_h  then
      i = i - (reg - Limit_h)
      reg = p + i + d
    end
    if reg < Limit_l  then
      i = i - (reg - Limit_l)
      reg = p + i + d
    end
    last_i = i
    return reg, last_i
  end

-- parametry symulacji
local expected = 1
local real = 0
local tmax = 5
Tp = 0.1

-- parametry regulatora
Kp = 10
Ti = 3
Td = 0.9
Limit_h = 15
Limit_l = 0

-- zmienne regulatora
local last_uchyb = 0
local last_i = 0
local reg = 0

-- pętla regulacji
File = io.open("result_pid.csv", "w")
for times = (0 + Tp), tmax, Tp
do
  local uchyb = expected - real
  reg, last_i = Regulator(uchyb, last_uchyb, last_i)
  last_uchyb = uchyb
  local f_times = string.gsub(string.format("%.1f", times), "%.", ",")
  local f_reg = string.gsub(string.format("%.8f", reg), "%.", ",")
  File:write(f_times,"\t",f_reg,"\t", "\n")
  print(times , string.format("%.6f",reg))
end
File:close()
print("ok")