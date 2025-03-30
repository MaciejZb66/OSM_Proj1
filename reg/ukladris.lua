
-- obiekt regulacji
function Inercja1(enter, last) -- 1/(5s+1)
  local out = (Tp / (5 + Tp)) * enter + (5 / (5 + Tp)) * last
  return out
end

function Inercja2(enter, last) -- 2/3s+1
  local out = ((Tp / (3 + Tp)) * enter + (3 / (3 + Tp)) * last/2)*2
  return out
end

function Obiekt(enter, last1, last2)
  local mid = Inercja1(enter, last1)
  local out = Inercja2(mid, last2)
  return out, mid
end

-- regulator PID
function Regulator(uchyb, last_uchyb, last_i)
  local p = Kp * uchyb
  local i = (Kp * 1/Ti * Tp * uchyb) + last_i
  local d = Kp * (uchyb - last_uchyb)/Tp * Td

  local reg = p + i + d
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
local expected = 10
local real = 0
local tmax = 20
Tp = 0.5

-- parametry regulatora
Kp = 10
Ti = 3
Td = 0.9
Limit_h = 15
Limit_l = 0

-- zmienne obiektu
local mid = 0

-- zmienne regulatora
local last_uchyb = 0
local last_i = 0
local reg = 0

-- pętla regulacji
File = io.open("result_uklad.csv", "w")
for times = (0 + Tp), tmax, Tp
do
  local uchyb = expected - real
  reg, last_i = Regulator(uchyb, last_uchyb, last_i)
  last_uchyb = uchyb
  real, mid = Obiekt(reg, mid, real)
  local f_times = string.gsub(string.format("%.1f", times), "%.", ",")
  local f_reg = string.gsub(string.format("%.8f", reg), "%.", ",")
  local f_real = string.gsub(string.format("%.8f", real), "%.", ",")
  File:write(f_times,"\t",f_reg,"\t",f_real, "\n")
  print(times ,string.format("%.6f",reg) , string.format("%.6f",real))
end
File:close()
print("ok")


